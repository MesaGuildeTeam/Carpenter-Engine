#ifndef ENGINE_BasicEvent
#define ENGINE_BasicEvent

#include <emscripten.h>

#include <vector>
#include <functional>

template <typename T>
class BasicEvent {
    private:
    std::vector<std::function<void(T)>> listeners;

    public:
    void subscribe(std::function<void(T)> listener) {
        listeners.push_back(listener);
    }

    void trigger(T arg) {
        for (auto listener : listeners) {
            listener(arg);
        }
    }
};

#endif