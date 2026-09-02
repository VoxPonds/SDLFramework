module;

export module engine.resource.resourcecache;

import engine.utilities;
import engine.resource.resourcehandle;
import engine.resource.resourcetraits;
import engine.resource.resourceptr;
import std;

export namespace engine::resource
{
	template<typename Resource>
	struct ResourceSlot
	{
		ResourcePtr<Resource> resource_ptr;
		std::uint32_t generation = 0;
	};

	template<typename Key, typename Resource, typename Loader>
	concept ResourceLoader =
		requires(Loader & loader, const Key & key)
		{
			{ loader(key) } -> std::same_as<ResourcePtr<Resource>>;
		};

	template<typename Key, typename Resource>
	concept MappingCheck =
		std::same_as<
			Key,
			typename ResourceTraits<Resource>::Key
		>;

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	class ResourceCache
	{
		using hash = ResourceTraits<Resource>::Hash;
		private:
			std::unordered_map<Key, ResourceHandle<Resource>, hash> key_to_handle_;
			std::vector<ResourceSlot<Resource>> slots_;
			std::vector<typename ResourceHandle<Resource>::IdType> free_slots_;

		public:
			bool contains(const Key& key) const;

			std::expected<ResourceHandle<Resource>, ResourceError> find(const Key& key)const;//find handle

			template<typename LoadFunc> requires ResourceLoader<Key, Resource, LoadFunc>
			std::expected<ResourceHandle<Resource>, ResourceError> load(const Key& key, LoadFunc load_func);

			std::expected<utilities::ObPtr<Resource>, ResourceError> get(ResourceHandle<Resource> handle);//get resource pointer

			std::expected<void, ResourceError> erase(const Key& key);
			void clear();
	};

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	bool ResourceCache<Key, Resource>::contains(const Key& key) const
	{
		return key_to_handle_.contains(key);
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	std::expected<ResourceHandle<Resource>, ResourceError> ResourceCache<Key, Resource>::find(const Key& key)const
	{
		auto it = key_to_handle_.find(key);
		if (it == key_to_handle_.end())
		{
			return std::unexpected(ResourceError::NOT_FOUND);
		}
		return it->second;
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	template<typename LoadFunc> requires ResourceLoader<Key,Resource,LoadFunc> 
	std::expected<ResourceHandle<Resource>,ResourceError> ResourceCache<Key, Resource>::load(const Key& key, LoadFunc load_func)
	{
		if (auto result = find(key); result) return result.value();

		auto resourcePtr = load_func(key);
		if (!resourcePtr) return std::unexpected(ResourceError::LOAD_FAILED);

		if (!free_slots_.empty())
		{
			const typename ResourceHandle<Resource>::IdType index = free_slots_.back();
			free_slots_.pop_back();
			auto& slot = slots_[index];
			slot.resource_ptr = std::move(resourcePtr);
			ResourceHandle<Resource> handle{ index, slot.generation };

			auto [it, inserted] = key_to_handle_.emplace(key, handle);
			if (!inserted)
			{
				std::unreachable();
			}
			return handle;
		}
		else
		{
			const auto index = static_cast<ResourceHandle<Resource>::IdType>(slots_.size());
			const typename ResourceHandle<Resource>::GenType generation = 0;

			slots_.emplace_back(std::move(resourcePtr), generation);
			//slots_.push_back({std::move(resource),generation});

			ResourceHandle<Resource> handle{ index, generation };

			auto [_it, _inserted] = key_to_handle_.emplace(key, handle);
			if (!_inserted)
			{
				std::unreachable();
			}

			return handle;
		}
	}

	template <typename Key, typename Resource> requires MappingCheck<Key, Resource>
	std::expected<utilities::ObPtr<Resource>, ResourceError> ResourceCache<Key, Resource>::get(ResourceHandle<Resource> handle)
	{
		if (!handle) return std::unexpected(ResourceError::INVALID_HANDLE);

		const auto index = handle.getId();

		if (index >= slots_.size()) return std::unexpected(ResourceError::INDEX_OUT_OF_RANGE);

		auto& slot = slots_[index];

		if (slot.generation != handle.getGeneration()) return std::unexpected(ResourceError::STALE_HANDLE);

		return slot.resource_ptr.get();
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	std::expected<void, ResourceError> ResourceCache<Key, Resource>::erase(const Key& key)
	{
		auto it = key_to_handle_.find(key);
		if (it == key_to_handle_.end()) return std::unexpected(ResourceError::NOT_FOUND);

		const auto handle = it->second;
		const auto id = handle.getId();

		auto& slot = slots_[id];

		slot.resource_ptr.reset();
		++slot.generation;

		free_slots_.push_back(id);
		key_to_handle_.erase(it);

		return {};
	}

	template<typename Key, typename Resource> requires MappingCheck<Key, Resource>
	void ResourceCache<Key, Resource>::clear()
	{
		free_slots_.clear();
		key_to_handle_.clear();

		for (auto index = 0; index < slots_.size(); ++index)
		{
			auto& slot = slots_[index];

			slot.resource_ptr.reset();
			++slot.generation;

			free_slots_.push_back(index);
		}
	}

}
