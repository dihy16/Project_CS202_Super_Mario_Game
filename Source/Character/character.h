#ifndef CHARACTER_H
#define CHARACTER_H

#include "./../definition.h"
#include "./../Map/items.h"
#include "./../Menu/saveGame.h"
#include "strategy.h"

class Item;             // forward declaration
class GameStateMemento; // forward declaration
class Level;            // forward declaration

class Character : public Entity
{
protected:
    Entity *character;
    std::unique_ptr<MoveStrategy> moveStrategy;
    SpriteRenderer *characterSprite;
    BoxCollider *characterCollider;

    sf::Clock timer1, timer2, timer3, stateTimer, touchTimer, finishTimer;
    std::string textureFile1, textureFile2;
    enum Direction
    {
        Right,
        Left
    } direction = Right;

public:
    bool goRight, goLeft, goUp, firing, created;
    bool eatMushroom, eatFlower, touchEnemy, touchFlag;
    enum State
    {
        Small,
        Super,
        Fire,
    } state = Small;
    RigidBody *characterRigidBody;

    Character(int x, int y, const std::string &texture1, const std::string &texture2);
    void moveRight(float speed);
    void moveLeft(float speed);
    void setRectForWalking(sf::IntRect &rect);
    void handleMovement(float speed);
    void handleEnemy();
    void handleMysteryBox(std::vector<std::unique_ptr<Item>> &items);
    void animation1(float duration, float interval, std::function<void()> onComplete, bool &finished);
    void animation2(float duration, float interval, std::function<void()> onComplete, bool &finished, State &state);
    void handlePowerUp();
    void handleFireball(std::vector<std::unique_ptr<Item>> &items);
    void update(std::vector<std::unique_ptr<Item>> &items, float speed);
    void stand();
    void freeFall();
    GameStateMemento saveState();
    void restoreState(const GameStateMemento &memento);

    friend class Level;
};

class Mario : public Character
{
public:
    Mario(int x, int y);
};

class Luigi : public Character
{
public:
    Luigi(int x, int y);
};
#endif // CHARACTER_H