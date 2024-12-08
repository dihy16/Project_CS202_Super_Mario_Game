#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <memory>

class MarioStateManager; // Forward declaration

// State Interface
class MarioState
{
public:
   virtual void handlePowerUp(MarioStateManager &manager) = 0;
   virtual void handleDamage(MarioStateManager &manager) = 0;
   virtual void performAction() = 0;
   virtual ~MarioState() = default;
};

// Concrete States
class SmallMario : public MarioState
{
public:
   void handlePowerUp(MarioStateManager &manager) override;
   void handleDamage(MarioStateManager &manager) override;
   void performAction() override;
};

class SuperMario : public MarioState
{
public:
   void handlePowerUp(MarioStateManager &manager) override;
   void handleDamage(MarioStateManager &manager) override;
   void performAction() override;
};

class InvincibleMario : public MarioState
{
public:
   void handlePowerUp(MarioStateManager &manager) override;
   void handleDamage(MarioStateManager &manager) override;
   void performAction() override;
};

// Context Class
class MarioStateManager
{
private:
   std::unique_ptr<MarioState> currentState;

public:
   MarioStateManager();
   void setState(std::unique_ptr<MarioState> newState);
   void handlePowerUp();
   void handleDamage();
   void performAction();
};

#endif