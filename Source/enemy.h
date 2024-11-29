// #include "definition.h"

// // Movement behavior interface (Strategy pattern)
// class MovementBehavior
// {
// public:
//    virtual void move() = 0;
//    virtual ~MovementBehavior() = default;
// };

// // Concrete movement behaviors
// class WalkBehavior : public MovementBehavior
// {
// public:
//    void move() override;
// };

// class JumpBehavior : public MovementBehavior
// {
// public:
//    void move() override;
// };

// // Enemy base class
// class Enemy
// {
// protected:
//    unique_ptr<MovementBehavior> movementBehavior;
//    bool isKilled, onGround, fading, display, moving;
//    int currentRect, maxRect;
//    float speed[2];
//    IntRect enemyRect;
//    Texture enemyTexture;
//    Clock timer;
//    Sprite enemySprite;

// public:
//    Enemy(int x, int y);
//    virtual void animation();
//    virtual void changeDirection();
//    virtual void checkGround();
//    virtual void checkKilled();
//    virtual void setKilled();
//    virtual void setFading();
//    virtual void draw(RenderWindow &window);
//    virtual ~Enemy() = default;
// };

// // Concrete enemy classes
// class Goomba : public Enemy
// {
// public:
//    Goomba(int x, int y);
//    void animation() override;
// };

// class Koopa : public Enemy
// {
// public:
//    Koopa(int x, int y);
//    void animation() override;
// };

// class HammerBro : public Enemy
// {
// public:
//    HammerBro(int x, int y);
//    void animation() override;
// };

// class PiranhaPlant : public Enemy
// {
// public:
//    PiranhaPlant(int x, int y);
//    void animation() override;
// };

// // Factory Method to create enemies
// class EnemyFactory
// {
// public:
//    static unique_ptr<Enemy> createEnemy(const string &type, int x, int y);
// };
