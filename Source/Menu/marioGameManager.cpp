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
    scoreMap[Goomba] = 100;
    scoreMap[Koopa] = 100;
    scoreMap[PiranhaPlant] = 100;
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
        // if (level)
        level->drawLevel();
        RenderManager::GetInstance().Update();
        getGUI()->draw(w);
        break;
    case GameState::pause:
        level->drawLevel();
        RenderManager::GetInstance().Update();
        getGUI()->draw(w);
        break;
    case GameState::status:
        updateGUI();
        // getGUI()->draw(w);
        getGUI()->drawStatus(w);
        break;
    case GameState::gameOver:
        updateGUI();
        getGUI()->draw(w);
        getGUI()->drawGameOver(w);
        break;
    case GameState::playerWin:
        getGUI()->setPlayerWinScore(getScore());
        getGUI()->drawPlayerWin(w);
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
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::E)
            {
                togglePause();
            }
        }
        break;
    case GameState::pause:
        if (ev.type == sf::Event::MouseButtonPressed)
        {
            if (getGUI()->handleClicking(w))
            {
                saveGame(level->saveMarioState(), MARIO_LOG);
            }
        }
        if (ev.type == sf::Event::KeyPressed)
        {
            if (ev.key.code == sf::Keyboard::E)
            {
                togglePause();
            }
        }
        break;
    case GameState::status:
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
    timer.restart();
    this->gameState = gameState;
}

void MarioGameManager::resetGame()
{
    setLives(3);
    setScore(0);
    setCoins(0);
    setTimeRemaining(300000);
}

void MarioGameManager::updateGameState(int delta_time, sf::Event &ev)
{
    switch (gameState)
    {
    case GameState::playing:
        playMusic(MarioGameManager::overworld);
        timeRemaining -= delta_time;
        // if (level)
        level->execute();
        break;
    case GameState::levelOver:

        break;
    case GameState::playerWin:
    case GameState::gameOver:
        stopMusic();
        if (timer.getElapsedTime().asSeconds() > 3.5f)
        {
            setState(GameState::menu);
            getMenuManager()->setMenuState(MenuManager::eMainMenu);
            timer.restart();
        }
        break;
    case GameState::pause:
        stopMusic();
        break;
    case GameState::menu:
        break;
    case GameState::status:
        stopMusic();
        if (timer.getElapsedTime().asSeconds() > 4.0f)
        {
            setState(GameState::playing);
            timer.restart();
        }
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
void MarioGameManager::marioDies()
{
    --marioLives;
    if (marioLives <= 0)
    {
        playSound(SoundName::game_over);
        updateHighScores(getScore(), getStringCurrentTime());
        saveHighScores(getVectorHiScore(), HIGHSCORE_FILE);
        setState(GameState::gameOver);
    }
    // else {
    //     setState(GameState::levelOver);
    // }
}

void MarioGameManager::loadLevel(bool resuming, bool isMarioSelected)
{
    std::cout << "resuming" << resuming << std::endl;
    // if (this->level)
    //     delete this->level;
    this->level = new Level(currentLevel, resuming, isMarioSelected);
}

void MarioGameManager::togglePause()
{
    if (gameState == GameState::playing)
    {
        playSound(SoundName::pause);
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
    timeRemaining = 300000;
    this->currentLevel = level;
}

void MarioGameManager::setIsMarioSelected(bool isMarioSelected)
{
    this->isMarioSelected = isMarioSelected;
}

bool MarioGameManager::getIsMarioSelected()
{
    return this->isMarioSelected;
}

void MarioGameManager::loadHiScore()
{
    vHighscore = loadHighScores(HIGHSCORE_FILE);
    std::sort(vHighscore.begin(), vHighscore.end(), [](const HighScoreEntry &a, const HighScoreEntry &b)
              { return a.score > b.score; });
}

const vector<HighScoreEntry> &MarioGameManager::getVectorHiScore()
{
    if (vHighscore.size() == 0)
        loadHiScore();
    return vHighscore;
}

std::string MarioGameManager::getStringCurrentTime()
{
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%d-%m-%Y-%H:%M:%S");
    return timeStream.str();
}

void MarioGameManager::updateHighScores(int newScore, const std::string &time)
{
    HighScoreEntry newEntry = {newScore, time};
    vHighscore.push_back(newEntry);
    std::sort(vHighscore.begin(), vHighscore.end(), [](const HighScoreEntry &a, const HighScoreEntry &b)
              { return a.score > b.score; });

    if (vHighscore.size() > TOTAL_HIGHSCORES)
    {
        vHighscore.resize(TOTAL_HIGHSCORES);
    }
}
