#ifndef DEFINITION_H
#define DEFINITION_H

#include "./PhysicsEngine/Managers/ComponentEntityManager.h"
#include "./PhysicsEngine/Components/BoxCollider.h"
#include "./PhysicsEngine/Components/RigidBody.h"
#include "./PhysicsEngine/Components/SpriteRenderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iomanip>
#include <memory>
#include <unordered_map>
#include <assert.h>
#include "./Menu/marioGameManager.h"

#define BLOCK_WIDTH 64
#define BLOCK_HEIGHT 64
#define MARIO "resource/Mario1.png"
#define SUPERMARIO "resource/MarioSuper2.png"
#define LUIGI "resource/Luigi1.png"
#define SUPERLUIGI "resource/LuigiSuper2.png"
#define ENEMY "resource/Enemies.png"
#define ITEM "resource/Items.png"
#define EXIT_BUTTON "resource/Menu/ExitButton.png"
#define MAP_LOG "resource/Log/game_log.txt"
#define MARIO_LOG "resource/Log/game_state.txt"
#define TILES "resource/TilesBackup.png"
#define HEART_ICON "resource/Heart.png"

#endif