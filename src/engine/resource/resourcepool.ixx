module;

export module engine.resource.resourcepool;

import engine.resource.resourceptr;
import engine.resource.resourcehandle;
import engine.utilities;
import std;

export namespace engine::resource
{
    template<typename Resource>
    struct ResourceSlot
    {
        ResourcePtr<Resource> resource_ptr {};
        std::uint32_t generation {};
    };

    template<typename Resource>
    class ResourcePool
    {
        private:
            std::vector<ResourceSlot<Resource>> m_slots_;
            std::vector<typename ResourceHandle<Resource>::IdType> m_free_slots_;

        public:
            auto create(ResourcePtr<Resource>&& resourcePtr) -> std::expected<ResourceHandle<Resource>, EResourceError>;

            auto get(ResourceHandle<Resource> handle) -> std::expected<util::ObPtr<Resource>, EResourceError>;

            auto erase(ResourceHandle<Resource> handle) -> std::expected<void, EResourceError>;

            void clear();
    };
}

namespace engine::resource
{
    template<typename Resource>
    auto ResourcePool<Resource>::create(ResourcePtr<Resource>&& resourcePtr) -> std::expected<ResourceHandle<Resource>, EResourceError>
    {
        if (!m_free_slots_.empty())
        {
            const typename ResourceHandle<Resource>::IdType index = m_free_slots_.back();
            m_free_slots_.pop_back();
            auto& slot = m_slots_[index];
            slot.resource_ptr = std::move(resourcePtr);
            ResourceHandle<Resource> handle{ index, slot.generation };
            return handle;
        }
        else
        {
            const auto index = static_cast<ResourceHandle<Resource>::IdType>(m_slots_.size());
            const typename ResourceHandle<Resource>::GenType generation {0};
            m_slots_.emplace_back(std::move(resourcePtr), generation);
            ResourceHandle<Resource> handle{ index, generation };
            return handle;
        }
    }

    template<typename Resource>
    auto ResourcePool<Resource>::get(ResourceHandle<Resource> handle) -> std::expected<util::ObPtr<Resource>, EResourceError>
    {
        if (!handle) return std::unexpected(EResourceError::INVALID_HANDLE);

        const auto index = handle.getId();

        if (index >= m_slots_.size()) return std::unexpected(EResourceError::INDEX_OUT_OF_RANGE);

        auto& slot = m_slots_[index];

        if (slot.generation != handle.getGeneration()) return std::unexpected(EResourceError::STALE_HANDLE);

        return util::observe(slot.resource_ptr.get());
    }

    template<typename Resource>
    auto ResourcePool<Resource>::erase(ResourceHandle<Resource> handle) -> std::expected<void, EResourceError>
    {
        if (!handle) return std::unexpected(EResourceError::INVALID_HANDLE);

        const auto id = handle.getId();

        if (id >= m_slots_.size()) return std::unexpected(EResourceError::INDEX_OUT_OF_RANGE);

        auto& slot = m_slots_[id];
        slot.resource_ptr.reset();
        ++slot.generation;
        m_free_slots_.emplace_back(id);
        return {};
    }

    template<typename Resource>
    void ResourcePool<Resource>::clear()
    {
        m_free_slots_.clear();
        for (std::size_t index = 0uz; index < m_slots_.size(); ++index)
        {
            auto& slot = m_slots_[index];

            slot.resource_ptr.reset();
            ++slot.generation;

            m_free_slots_.emplace_back(index);
        }
    }
}
