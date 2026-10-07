module;

export module engine.resource.resourcecache;

import engine.utilities;
import engine.resource.resourcepool;
import engine.resource.resourcehandle;
import engine.resource.resourcetraits;
import engine.resource.resourceptr;
import std;

export namespace engine::resource
{
	template<typename Key, typename Resource, typename Loader>
	concept ResourceLoader = requires(const Loader& loader, const Key& key)
	{
		{ loader(key) } -> std::same_as<ResourcePtr<Resource>>;
	};

	template<typename Key, typename Resource>
	concept MappingCheck = std::same_as<Key, typename ResourceTraits<Resource>::Key>;

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	class ResourceCache
	{
		private:
			std::unordered_map<Key, ResourceHandle<Resource>, typename ResourceTraits<Resource>::Hash> m_key_to_handle_;
			ResourcePool<Resource> m_resource_pool_;

		public:
			bool contains(const Key& key) const;

			auto find(const Key& key)const -> std::expected<ResourceHandle<Resource>, EResourceError>;//find handle

			template<typename LoadFunc> requires ResourceLoader<Key, Resource, LoadFunc>
			auto load(const Key& key, LoadFunc load_func) -> std::expected<ResourceHandle<Resource>, EResourceError>;

			auto get(ResourceHandle<Resource> handle) -> std::expected<util::ObPtr<Resource>, EResourceError>;//get resource pointer

			auto erase(const Key& key) -> std::expected<void, EResourceError>;

			void clear();
	};
}

namespace engine::resource
{
	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	bool ResourceCache<Key, Resource>::contains(const Key& key) const
	{
		return m_key_to_handle_.contains(key);
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	auto ResourceCache<Key, Resource>::find(const Key& key) const -> std::expected<ResourceHandle<Resource>, EResourceError>
	{
		auto it = m_key_to_handle_.find(key);
		if (it == m_key_to_handle_.end())
		{
			return std::unexpected(EResourceError::NOT_FOUND);
		}
		return it->second;
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	template<typename LoadFunc> requires ResourceLoader<Key,Resource,LoadFunc>
	auto ResourceCache<Key, Resource>::load(const Key& key, LoadFunc load_func) -> std::expected<ResourceHandle<Resource>, EResourceError>
	{
		if (auto result {find(key)}; result) return result.value();

		auto resourcePtr = load_func(key);
		if (!resourcePtr) return std::unexpected(EResourceError::LOAD_FAILED);

		if (const auto handle_result { m_resource_pool_.create(std::move(resourcePtr)) })
		{
			auto [it, inserted] = m_key_to_handle_.emplace(key, handle_result.value());
			if (!inserted)
			{
				std::invoke_r<void>(&ResourcePool<Resource>::erase, m_resource_pool_, handle_result.value());
				//m_resource_pool_.erase(handle_result.value());
				return it->second;
			}
			return handle_result.value();
		}
		else
		{
			return std::unexpected(handle_result.error());
		}
	}

	template <typename Key, typename Resource> requires MappingCheck<Key, Resource>
	auto ResourceCache<Key, Resource>::get(ResourceHandle<Resource> handle) -> std::expected<util::ObPtr<Resource>, EResourceError>
	{
		return m_resource_pool_.get(handle);
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	auto ResourceCache<Key, Resource>::erase(const Key& key) -> std::expected<void, EResourceError>
	{
		auto it = m_key_to_handle_.find(key);
		if (it == m_key_to_handle_.end()) return std::unexpected(EResourceError::NOT_FOUND);

		const auto result = m_resource_pool_.erase(it->second);
		m_key_to_handle_.erase(it);

		return result;
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	void ResourceCache<Key, Resource>::clear()
	{
		m_key_to_handle_.clear();
		m_resource_pool_.clear();
	}
}
