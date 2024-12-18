#ifndef CHARACTER_H
#define CHARACTER_H

#include "./PhysicsEngine/Managers/ComponentEntityManager.h"
#include "./PhysicsEngine/Components/BoxCollider.h"
#include "./PhysicsEngine/Components/RigidBody.h"
#include "./PhysicsEngine/Components/SpriteRenderer.h"
#include "./items.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "marioGameManager.h"
#include "saveGame.h"

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64
#define MARIO "resource/Mario1.png"
#define SUPERMARIO "resource/MarioSuper2.png"
#define LUIGI "resource/Luigi1.png"
#define SUPERLUIGI "resource/LuigiSuper2.png"

class Item;             // forward declaration
class GameStateMemento; // forward declaration
class Level;            // forward declaration

class Character : public Entity
{
protected:
    Entity *character;

    SpriteRenderer *characterSprite;
    BoxCollider *characterCollider;

    sf::Clock timer1, timer2, timer3, stateTimer, touchTimer;
    std::string textureFile1, textureFile2;

    enum Direction
    {
        Right,
        Left
    } direction = Right;

public:
    bool goRight, goLeft, goUp, firing, created;
    bool eatMushroom, eatFlower, touchEnemy;
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
    void animation1(float duration, float interval, std::function<void()> onComplete, bool &finished);
    void animation2(float duration, float interval, std::function<void()> onComplete, bool &finished, State &state);
    void handlePowerUp();
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