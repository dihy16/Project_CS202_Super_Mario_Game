#include "strategy.h"

void MoveStrategy::move(float speedX, float speedY) {}

void CharacterMoveStrategy::move(float speedX, float speedY)
{
   if (character.goRight == character.goLeft)
      character.characterRigidBody->xVel = 0;
   else if (character.goRight)
      character.moveRight(speedX);
   else if (character.goLeft)
      character.moveLeft(speedX);

   if (!character.goRight && !character.goLeft && !character.characterRigidBody->isJumping && !character.firing)
      character.stand();
}

void EnemyMoveStrategy::move(float speedX, float speedY)
{
   enemy.getRigidBody()->xVel = speedX;
   enemy.getRigidBody()->yVel = speedY;
}