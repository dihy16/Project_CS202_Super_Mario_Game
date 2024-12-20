#include "marioGameManager.h"

MarioGameManager *MarioGameManager::instance = nullptr;
MarioGameManager::GameState MarioGameManager::gameState = GameState::menu;

MarioGameManager::MarioGameManager()
{
    menuManager = new MenuManager();
    GUIManager = new GUI();
    initScoreMap();
    loadHiScore();
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
    if (instance == nullptr)
    {
        instance = new MarioGameManager();
    }
    return instance;
}

MarioGameManager::~MarioGameManager()
{
    delete menuManager;
    delete GUIManager;
    delete instance;
    delete level;
}

MenuManager *MarioGameManager::getMenuManager()
{
    return this->menuManager;
}

GUI *MarioGameManager::getGUI()
{
    return this->GUIManager;
}

Level *MarioGameManager::getLevel()
{
    return this->level;
}

void MarioGameManager::updateGUI()
{
    getGUI()->setCoin(marioCoins);
    getGUI()->setLives(marioLives);
    getGUI()->setTimeRemaining(timeRemaining / 1000);
    getGUI()->setScore(score);
    getGUI()->setStatus(marioLives, MarioGameManager::getInstance()->getCurrentLevel());
}

void MarioGameManager::run()
{
    setState(GameState::menu);
}
void MarioGameManager::draw(sf::RenderWindow &w)
{
    switch (gameState)
    {
    case GameState::menu:
        menuManager->draw(w);
        break;
    case GameState::playing:
        updateGUI();
        if (level)
            level->drawLevel();
        RenderManager::GetInstance().Update();
        getGUI()->draw(w);
        getGUI()->drawExitButton(w);
        break;
    case GameState::pause:
        level->drawLevel();
        RenderManager::GetInstance().Update();
        getGUI()->draw(w);
        getGUI()->drawExitButton(w);
        break;
    case GameState::status:
        updateGUI();
        getGUI()->draw(w);
        getGUI()->drawStatus(w);
        break;
    case GameState::gameOver:
        updateGUI();
        getGUI()->draw(w);
        getGUI()->drawGameOver(w);
        break;
    default:
        break;
    }
}

void MarioGameManager::handleEvents(sf::RenderWindow &w, sf::Event &ev)
{
    switch (gameState)
    {
    case GameState::menu:
        menuManager->handleEvents(w, ev);
        break;
    case GameState::playing:
        if (ev.type == sf::Event::MouseButtonPressed)
        {
            getGUI()->handleClicking(w);
        }
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::P)
            {
                togglePause();
            }
        }
        if (level)
            level->execute();
        break;
    case GameState::pause:
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::P)
            {
                togglePause();
            }
        }
        break;
    case GameState::status:
        // if (ev.type == sf::Event::MouseButtonPressed)
        //{
        //     int isMario = getGUI()->getStatusScr()->handleCharacterSelection(w);
        //     std::cout << "isMario" << isMario << std::endl;
        //     if (isMario == -1)
        //         break;
        //     loadLevel(false, isMario);
        //     setState(MarioGameManager::GameState::playing);
        // }
        break;
    }
}

void MarioGameManager::addScore(ScoreID scoreId)
{
    score += scoreMap[scoreId];
}

void MarioGameManager::addCoin()
{
    ++marioCoins;
    if (marioCoins >= 40)
    {
        marioCoins = 0;
        addLive();
    }
}

void MarioGameManager::addLive()
{
    ++marioLives;
}

void MarioGameManager::setState(GameState gameState)
{
    this->gameState = gameState;
}

void MarioGameManager::updateGameState(int delta_time, sf::Event &ev)
{
    switch (gameState)
    {
    case GameState::playing:
        playMusic(MarioGameManager::overworld);
        timeRemaining -= delta_time;
        // if (level)
        //     level->execute();
        break;
    case GameState::levelOver:

        break;
    case GameState::gameOver:
        if (timer.getElapsedTime().asSeconds() > 3.5f)
        {
            setState(GameState::menu);
            timer.restart();
        }
        break;
    case GameState::pause:
        stopMusic();
        break;
    case GameState::menu:
        break;
    case GameState::status:
        if (timer.getElapsedTime().asSeconds() > 3.5f)
        {
            setState(GameState::playing);
            timer.restart();
        }
        break;
    default:
        break;
    }
}

int MarioGameManager::getLives() { return marioLives; }
int MarioGameManager::getCoins() { return marioCoins; }
int MarioGameManager::getScore() { return score; }
int MarioGameManager::getTimeRemaining() { return timeRemaining; }

void MarioGameManager::setLives(int lives) { marioLives = lives; }
void MarioGameManager::setCoins(int coins) { marioCoins = coins; }
void MarioGameManager::setScore(int score) { this->score = score; }
void MarioGameManager::setTimeRemaining(int time) { timeRemaining = time; }
void MarioGameManager::setIsMarioSelected(bool isMarioSelected) { this->isMarioSelected = isMarioSelected; }
void MarioGameManager::marioDies()
{
    --marioLives;
    if (marioLives <= 0)
    {
        setState(GameState::gameOver);
    }
    // else {
    //     setState(GameState::levelOver);
    // }
}

void MarioGameManager::loadLevel(bool resuming, bool isMario)
{
    std::cout << "resuming" << resuming << std::endl;
    this->level = new Level(currentLevel, resuming, isMario);
}

void MarioGameManager::togglePause()
{
    if (gameState == GameState::playing)
    {
        setState(GameState::pause);
    }
    else if (gameState == GameState::pause)
    {
        setState(GameState::playing);
    }
}

int MarioGameManager::getCurrentLevel()
{
    return currentLevel;
}

void MarioGameManager::setCurrentLevel(int level)
{
    timer.restart();
    this->currentLevel = level;
}

void MarioGameManager::loadHiScore()
{
    vHighscore = loadHighScores(HIGHSCORE_FILE);
}

vector<int> MarioGameManager::getVectorHiScore()
{
    return vHighscore;
}
