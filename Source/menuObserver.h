class IGameStateObserver {
public:
    virtual ~IGameStateObserver() = default;
    virtual void changeState(int newState) = 0; // Notify the observer of state changes
};
