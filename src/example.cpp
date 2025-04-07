#include <iostream>

#include "events.h"

void UI_HealthBar(const char* dmg)
{
    std::cout << "[UI] Player took damage: " << dmg << std::endl;
}

class Analytics
{
public:
    void LogDamage(const char* dmg)
    {
        std::cout << "[Analytics] Logged damage: " << dmg << std::endl;
    }
};

int main()
{
    EventDispatcher<const char*> Dispatcher;

    // Subscribe plain function
    Dispatcher.AddListener(UI_HealthBar);

    // Subscribe lambda
    Analytics analytics;
    std::function<void(const char*)> func = [&analytics](const char* dmg) { analytics.LogDamage(dmg); };

    Dispatcher.AddListener(func);

    Dispatcher.Broadcast("65");

    return 0;
}