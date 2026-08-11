module;


export module engine.resource.sdlresourcecache;
import std.compat;
import engine.platform.sdlptr;
import engine.utilities;
import engine.resource.resourcehandle;

export namespace engine::resource
{
	struct TextureKey
	{
		std::string path;
		bool operator==(const TextureKey&) const = default;
	};

	template<typename Resource>
	struct ResourceSlot
	{
		platform::SdlPtr<Resource> resource_ptr;
		std::uint32_t generation = 0;
	};

	template<typename T>
	struct KeyHash;

	template<>
	struct KeyHash<TextureKey>
	{
		size_t operator()(const TextureKey& key) const
		{
			return utilities::makeHash(key.path);
		}
	};

	template<typename Key, typename Resource, typename Loader>
	concept ResourceLoader =
		requires(Loader loader, const Key & key)
		{
			{ loader(key) } -> std::same_as<platform::SdlPtr<Resource>>;
		};

	template<typename Key, typename Resource>
	class SdlResourceCache
	{
		protected:
			std::unordered_map<Key, ResourceHandle<Resource>, KeyHash<Key>> key_to_handle_;
			std::vector<ResourceSlot<Resource>> slots_;

		public:
			bool contains(const Key& key) const;

			ResourceHandle<Resource> find(const Key& key)const;//find handle

			template<typename LoadFunc> requires ResourceLoader<Key,Resource,LoadFunc>
			ResourceHandle<Resource> load(const Key& key, LoadFunc load_func);

			platform::SdlObPtr<Resource> get(const ResourceHandle<Resource> handle);//get resource pointer

			bool erase(const Key& key);
			void clear();
	};

	template<typename Key, typename Resource>
	bool SdlResourceCache<Key, Resource>::contains(const Key& key) const
	{
		return key_to_handle_.contains(key);
	}

	template<typename Key, typename Resource>
	ResourceHandle<Resource> SdlResourceCache<Key, Resource>::find(const Key& key)const
	{
		if (auto it = key_to_handle_.find(key); it != key_to_handle_.end()) return it->second;
		return ResourceHandle<Resource>{};
	}

	template<typename Key, typename Resource>
	template<typename LoadFunc> requires ResourceLoader<Key, Resource, LoadFunc>
	ResourceHandle<Resource> SdlResourceCache<Key, Resource>::load(const Key& key, LoadFunc load_func)
	{
		
		if (auto it = key_to_handle_.find(key); it != key_to_handle_.end()) return it->second;

		const auto index = static_cast<ResourceHandle<Resource>::ValueType>(slots_.size());
		const typename ResourceHandle<Resource>::ValueType generation = 0;
		ResourceHandle<Resource> handle{ index,generation };

		auto [new_it, inserted] = key_to_handle_.emplace(key, handle);

		auto resource = load_func(key);
		slots_.emplace_back(std::move(resource),generation);
		//slots_.push_back({std::move(resource),generation});

		return new_it->second;
	}

	template <typename Key, typename Resource>
	platform::SdlObPtr<Resource> SdlResourceCache<Key, Resource>::get(const ResourceHandle<Resource> handle)
	{
		if (!handle) return nullptr;

		const auto index = handle.getId();

		if (index >= slots_.size()) return nullptr;

		auto& slot = slots_[index];

		if (slot.generation != handle.generation()) return nullptr;

		return slot.resource_ptr.get();
	}

	template<typename Key, typename Resource>
	bool SdlResourceCache<Key, Resource>::erase(const Key& key)
	{
		//return slots_.empty(), key_to_handle_.erase(key) > 0;
		return false;
	}

	template<typename Key, typename Resource>
	void SdlResourceCache<Key, Resource>::clear()
	{
		key_to_handle_.clear();
		slots_.clear();
	}

}
