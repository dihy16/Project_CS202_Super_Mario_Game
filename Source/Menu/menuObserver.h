#ifndef MENU_OBSERVER_H
#define MENU_OBSERVER_H

class IGameStateObserver {
public:
    virtual ~IGameStateObserver() = default;
    virtual void changeState(int newState) = 0; // Notify the observer of state changes
};
#endif // !MENU_OBSERVER_H
