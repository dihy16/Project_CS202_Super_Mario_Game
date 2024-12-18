#include "marioGameManager.h"

MarioGameManager* MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    GUIManager = new GUI();
    lv1 = new Level(1);
    initScoreMap();
}

void MarioGameManager::initScoreMap()
{
    scoreMap[Coin] = 200;
    scoreMap[Mushroom] = 1000;
    scoreMap[Flower] = 1000;
    scoreMap[Star] = 1000;
}

MarioGameManager *MarioGameManager::getInstance()
{
    if (instance == nullptr) {
        instance = new MarioGameManager();
    }
    return instance;
}

MarioGameManager::~MarioGameManager()
{
    delete menuManager;
    delete GUIManager;
    delete instance;
}

MenuManager *MarioGameManager::getMenuManager()
{
    return this->menuManager;
}

GUI* MarioGameManager::getGUI()
{
    return this->GUIManager;
}

void MarioGameManager::updateGUI()
{
    getGUI()->setCoin(marioCoins);
    getGUI()->setLives(marioLives);
    getGUI()->setTimeRemaining(timeRemaining / 1000);
    getGUI()->setScore(score);
}

void MarioGameManager::run()
{
    setState(GameState::menu);
}
void MarioGameManager::draw(sf::RenderWindow &w)
{
    switch (gameState) {
    case GameState::menu:
        menuManager->draw(w);
        break;
    case GameState::playing:
        if (lv1) lv1->drawLevel();
        RenderManager::GetInstance().Update();
        updateGUI();
        getGUI()->draw(w);
        break;
    case GameState::pause:
        RenderManager::GetInstance().Update();
        getGUI()->draw(w);
        break;
    }

}

void MarioGameManager::handleEvents(sf::RenderWindow &w, sf::Event &ev)
{
    switch (gameState) {
        case GameState::menu:
            menuManager->handleEvents(w, ev);
        break;
        case GameState::playing:
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::P) {
                    togglePause();
                }
            }
         break;
        case GameState::pause:
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::P) {
                    togglePause();
                }
            }
            break;
    }
}

void MarioGameManager::addScore(ScoreID scoreId)
{
    score += scoreMap[scoreId];
}

// Map *MarioGameManager::getMap()
// {
//     return map;
// }

// Mario *MarioGameManager::getMario()
// {
//     return theman;
// }

void MarioGameManager::addCoin()
{
    ++marioCoins;
    if (marioCoins >= 40) {
        marioCoins = 0;
        addLive();
    }
    // addScore(ScoreID::Coin);
    // getGUI()->setCoin(marioCoins);
}

void MarioGameManager::addLive()
{
    ++marioLives;
}

void MarioGameManager::setState(GameState gameState)
{
    this->gameState = gameState;
}

void MarioGameManager::updateGameState(int delta_time, sf::Event& ev)
{
    switch (gameState) {
    case GameState::playing:
        playMusic(MarioGameManager::overworld);
        timeRemaining -= delta_time;
        if (lv1) lv1->execute();
        break;
    case GameState::levelOver:
        
        break;
    case GameState::gameOver:
        setState(GameState::menu);
        break;
    case GameState::pause:

        break;
    case GameState::menu:
        break;
    }
}

void MarioGameManager::marioDies()
{
    --marioLives;
    if (marioLives <= 0) {
        setState(GameState::gameOver);
    } 
    //else {
    //    setState(GameState::levelOver);
    //}
}

int MarioGameManager::loadLevel(const std::string &level_name)
{

    return 0;
}

void MarioGameManager::togglePause()
{
    if (gameState == GameState::playing) {
        setState(GameState::pause);
    }
    else if (gameState == GameState::pause){
        setState(GameState::playing);
    }
    
}

Level::Level(int level)
{
    mario = new Mario(8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    m = new Map;
    m->loadmap(level, 8 * BLOCK_WIDTH, 12 * BLOCK_HEIGHT);
    sf::Color c;
    std::string whichlevel;
    switch (level)
    {
    case 1:
        whichlevel = "Data/Level1";
        break;
    case 2:
        whichlevel = "Data/Level2";
        break;
    case 3:
        whichlevel = "Data/Level3";
        break;
    }
    entitylayout.loadFromFile(whichlevel + "/entity.png");
    for (int i = 0; i < entitylayout.getSize().y; i++)
    {
        for (int j = 0; j < entitylayout.getSize().x; j++)
        {
            c = sf::Color(entitylayout.getPixel(j, i));
            if (c == sf::Color(95, 205, 228)); //nothing
            else if (c == sf::Color(143, 86, 59))
                enemies.push_back(EnemyFactory::createEnemy("Goomba", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(153, 229, 80))
                enemies.push_back(EnemyFactory::createEnemy("Koopa", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(106, 190, 48))
                enemies.push_back(EnemyFactory::createEnemy("HammerBro", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
            else if (c == sf::Color(255, 255, 0))
                enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", j * BLOCK_WIDTH, i * BLOCK_HEIGHT));
        }
    }
    // enemies.push_back(EnemyFactory::createEnemy("Goomba", 300, 0));
    // enemies.push_back(EnemyFactory::createEnemy("Koopa", 400, 0));
    // enemies.push_back(EnemyFactory::createEnemy("PiranhaPlant", 500, 0));
    // enemies.push_back(EnemyFactory::createEnemy("HammerBro", 400, 700));
    // items.push_back(ItemFactory::createItem("Mushroom", 200, 700));
    // items.push_back(ItemFactory::createItem("Coin", 500, 700));
    // items.push_back(ItemFactory::createItem("Coin", 600, 700));
    // items.push_back(ItemFactory::createItem("Coin", 700, 700));
    enemies.push_back(EnemyFactory::createEnemy("Goomba", 200, 0));
    items.push_back(ItemFactory::createItem("Flower", 350, 700));
};
void Level::start()
{
    display = true;
}
void Level::end()
{
    display = false;
}

void Level::handleKeyPress()
{
    mario->goLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    mario->goRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    mario->firing = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    mario->marioRigidBody->isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

void Level::execute()
{
    if (MarioGameManager::getInstance()->getState() == MarioGameManager::GameState::pause) return;
    handleKeyPress();
    mario->update(items);
    for (auto& enemy : enemies)
    {
        enemy->move();
        enemy->collideWithMario(*mario);
        enemy->fadingAnimation();
    }

    for (auto& item : items)
    {
        item->animation();
        item->fadeOut();
    }
}

void Level::drawLevel()
{
    m->draw(RenderManager::GetInstance().window);
}
