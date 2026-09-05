module;

export module engine.core.eventdispatcher;
import std;

export namespace engine::core
{
    template<typename Event, typename Callback>
    concept CallBackConstraint =
        requires {std::invocable<Callback, const Event&>;};

    class EventDispatcher
    {
        private:
            std::size_t next_id_{0};
            using EventCallback = std::function<void(const void*)>;
            struct Listener{std::size_t id; EventCallback callback;};
            std::unordered_map<std::type_index, std::vector<Listener>> observers_mapping_;

            class EventConnection
            {
                friend class EventDispatcher;
                private:
                    std::size_t id_;
                    EventDispatcher& dispatcher_;
                    bool connected_;

                public:
                    EventConnection(std::size_t id, EventDispatcher &dispatcher):
                        id_(id), dispatcher_(dispatcher), connected_(true)
                    {
                    }

                    EventConnection() = delete;
                    ~EventConnection()
                    {
                        disconnect();
                    };

                    EventConnection(EventConnection&&) = delete;
                    EventConnection& operator=(EventConnection&&) = delete;
                    EventConnection(const EventConnection&) = delete;
                    EventConnection& operator=(const EventConnection&) = delete;

                    void disconnect();
                    bool connected() const;
            };
            void remove(std::size_t id);

        public:
            template<typename Event, typename Callback> requires CallBackConstraint<Event, Callback>
            EventConnection subscribe(Callback&& callback);

            template<typename Event>
            void dispatch(const Event& event);
    };

    void EventDispatcher::EventConnection::disconnect()
    {
        if (!connected_) return;

        dispatcher_.remove(id_);
        connected_ = false;
    }

    bool EventDispatcher::EventConnection::connected() const
    {
        return connected_;
    }

    void EventDispatcher::remove(std::size_t id)
    {
        for (auto& observers: observers_mapping_ | std::views::values)
        {
            std::erase_if(
                observers,
                [id](const Listener& listener)
                {
                    return listener.id == id;
                }
            );
        }
    }

    template<typename Event, typename Callback> requires CallBackConstraint<Event, Callback>
    EventDispatcher::EventConnection EventDispatcher::subscribe(Callback&& callback)
    {
        auto& observers = observers_mapping_[std::type_index(typeid(Event))];
        const auto id = next_id_++;
        observers.emplace_back(
            id,
            [callback = std::forward<Callback>(callback)](const void* event) -> void
            {
                callback(*static_cast<const Event*>(event));
            }
        );
        return EventConnection{id, *this };
    }

    template<typename Event>
    void EventDispatcher::dispatch(const Event &event)
    {
        const auto it = observers_mapping_.find(std::type_index(typeid(Event)));
        if (it == observers_mapping_.end()) return;

        for (const auto& listener : it->second)
        {
            listener.callback(&event);
        }
    }
}
