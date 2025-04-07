
#pragma once

#include <vector>
#include <functional>
#include <algorithm>


template<typename... Args>
class EventDispatcher
{
public:
    using Callback = std::function<void(Args...)>;
    using ListenerId = std::size_t;

    // Subscribe to the event
    ListenerId AddListener(Callback callback)
    {
        Listener listener;
        listener.id = nextId++;
        listener.callback = std::move(callback);
        listeners.push_back(std::move(listener));
        return listener.id;
    }

    // Remove a listener by id
    void RemoveListener(ListenerId id)
    {
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
    }

    // Trigger the event
    void Broadcast(Args... args)
    {
        for (const auto& listener : listeners)
        {
            listener.callback(args...);
        }
    }

    private:

    struct Listener
    {
        ListenerId id;

        Callback callback;

        void notify(Args... args) { callback(args...); }
    
    };


    std::vector<Listener> listeners;
    ListenerId nextId = 1;
};