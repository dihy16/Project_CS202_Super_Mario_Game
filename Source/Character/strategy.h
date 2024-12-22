#ifndef STRATEGY_H
#define STRATEGY_H
#include "character.h"
#include "enemy.h"

class Character;
class Enemy;
class MoveStrategy
{
public:
   virtual void move(float speedX, float speedY) = 0;
   virtual ~MoveStrategy() {}
};

class CharacterMoveStrategy : public MoveStrategy
{
private:
   Character &character;

public:
   CharacterMoveStrategy(Character &character) : character(character) {}
   void move(float speedX, float speedY) override;
};

class EnemyMoveStrategy : public MoveStrategy
{
private:
   Enemy &enemy;

public:
   EnemyMoveStrategy(Enemy &enemy) : enemy(enemy) {}
   void move(float speedX, float speedY) override;
};

#endif