#include "./marioState.h"

void SmallMario::handlePowerUp(MarioStateManager &manager)
{
   // when small gets item --> become super
   manager.setState(std::make_unique<SuperMario>());
}

void SmallMario::handleDamage(MarioStateManager &manager)
{
   // when small gets damage --> die
   std::cout << "Mario died" << std::endl;
}

void SmallMario::performAction()
{
   // small mario action
   std::cout << "Small Mario" << std::endl;
}

void SuperMario::handlePowerUp(MarioStateManager &manager)
{
   // when super gets item --> become invincible
   manager.setState(std::make_unique<InvincibleMario>());
}

void SuperMario::handleDamage(MarioStateManager &manager)
{
   // when super gets damage --> become small
   manager.setState(std::make_unique<SmallMario>());
}

void SuperMario::performAction()
{
   // super mario action
   std::cout << "Super Mario" << std::endl;
}

void InvincibleMario::handlePowerUp(MarioStateManager &manager)
{
   // when invincible gets item --> does not change
}

void InvincibleMario::handleDamage(MarioStateManager &manager)
{
   manager.setState(std::make_unique<SuperMario>());
}

void InvincibleMario::performAction()
{
   // invincible mario action
   std::cout << "Invincible Mario" << std::endl;
}

MarioStateManager::MarioStateManager()
{
   currentState = std::make_unique<SmallMario>();
}

void MarioStateManager::setState(std::unique_ptr<MarioState> newState)
{
   currentState = std::move(newState);
}

void MarioStateManager::handlePowerUp()
{
   currentState->handlePowerUp(*this);
}

void MarioStateManager::handleDamage()
{
   currentState->handleDamage(*this);
}

void MarioStateManager::performAction()
{
   currentState->performAction();
}