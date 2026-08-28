module;
#include "filesystem"

export module engine.resource.sdlresourcecache;

import engine.platform.sdlptr;
import engine.utilities;
import engine.resource.resourcehandle;
import std;

export namespace engine::resource
{
	struct TextureKey
	{
		std::filesystem::path path;
		bool operator==(const TextureKey&) const = default;
	};

	template<typename T>
	struct KeyHash;

	template<>
	struct KeyHash<TextureKey>
	{
		size_t operator()(const TextureKey& key) const noexcept
		{
			return utilities::makeHash(key.path);
		}
	};

	template<typename Resource>
	struct ResourceSlot
	{
		platform::SdlPtr<Resource> resource_ptr;
		std::uint32_t generation = 0;
	};

	template<typename Key, typename Resource, typename Loader>
	concept ResourceLoader =
		requires(Loader& loader, const Key & key)
		{
			{ loader(key) } -> std::same_as<platform::SdlPtr<Resource>>;
		};

	template<typename Key, typename Resource>
	class SdlResourceCache
	{
		private:
			std::unordered_map<Key, ResourceHandle<Resource>, KeyHash<Key>> key_to_handle_;
			std::vector<ResourceSlot<Resource>> slots_;
			std::vector<typename ResourceHandle<Resource>::IdType> free_slots_;

		public:
			bool contains(const Key& key) const;

			std::expected<ResourceHandle<Resource>, ResourceError> find(const Key& key)const;//find handle

			template<typename LoadFunc> requires ResourceLoader<Key,Resource,LoadFunc>
			std::expected<ResourceHandle<Resource>, ResourceError> load(const Key& key, LoadFunc load_func);

			std::expected<utilities::ObPtr<Resource>, ResourceError> get(const ResourceHandle<Resource> handle);//get resource pointer

			std::expected<void, ResourceError> erase(const Key& key);
			void clear();
	};

	template<typename Key, typename Resource>
	bool SdlResourceCache<Key, Resource>::contains(const Key& key) const
	{
		return key_to_handle_.contains(key);
	}

	template<typename Key, typename Resource>
	std::expected<ResourceHandle<Resource>, ResourceError> SdlResourceCache<Key, Resource>::find(const Key& key)const
	{
		if (auto it = key_to_handle_.find(key); it != key_to_handle_.end())
		{
			if (slots_[it->second.getId()].generation == it->second.getGeneration())
			{
				return it->second;
			}
			return std::unexpected(ResourceError::StaleHandle);
		}
		return std::unexpected(ResourceError::NotFound);

	}

	template<typename Key, typename Resource>
	template<typename LoadFunc> requires ResourceLoader<Key, Resource, LoadFunc>
	std::expected<ResourceHandle<Resource>,ResourceError> SdlResourceCache<Key, Resource>::load(const Key& key, LoadFunc load_func)
	{
		if (auto result = find(key); result) return result.value();

		auto resourcePtr = load_func(key);
		if (!resourcePtr) return std::unexpected(ResourceError::LoadFailed);

		if (!free_slots_.empty())
		{
			const typename ResourceHandle<Resource>::IdType index = free_slots_.back();
			free_slots_.pop_back();
			auto& slot = slots_[index];
			slot.resource_ptr = std::move(resourcePtr);
			ResourceHandle<Resource> handle{ index, slot.generation };
			key_to_handle_.emplace(key, handle);
			return handle;
		}
		else
		{
			const auto index = static_cast<ResourceHandle<Resource>::IdType>(slots_.size());
			const typename ResourceHandle<Resource>::GenType generation = 0;

			slots_.emplace_back(std::move(resourcePtr), generation);
			//slots_.push_back({std::move(resource),generation});

			ResourceHandle<Resource> handle{ index, generation };

			key_to_handle_.emplace(key, handle);

			return handle;
		}
		
	}

	template <typename Key, typename Resource>
	std::expected<utilities::ObPtr<Resource>, ResourceError> SdlResourceCache<Key, Resource>::get(const ResourceHandle<Resource> handle)
	{
		if (!handle) return std::unexpected(ResourceError::InvalidHandle);

		const auto index = handle.getId();

		if (index >= slots_.size()) return std::unexpected(ResourceError::IndexOutOfRange);

		auto& slot = slots_[index];

		if (slot.generation != handle.getGeneration()) return std::unexpected(ResourceError::StaleHandle);

		return slot.resource_ptr.get();
	}

	template<typename Key, typename Resource>
	std::expected<void, ResourceError> SdlResourceCache<Key, Resource>::erase(const Key& key)
	{
		auto it = key_to_handle_.find(key);
		if (it == key_to_handle_.end()) return std::unexpected(ResourceError::NotFound);

		const auto handle = it->second;
		const auto id = handle.getId();

		auto& slot = slots_[id];

		slot.resource_ptr.reset();
		++slot.generation;

		free_slots_.push_back(id);
		key_to_handle_.erase(it);

		return {};
	}

	template<typename Key, typename Resource>
	void SdlResourceCache<Key, Resource>::clear()
	{
		slots_.clear();
		key_to_handle_.clear();
	}

}
