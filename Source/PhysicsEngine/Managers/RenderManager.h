#ifndef _RenderManager_h_
#define _RenderManager_h_
#include "../Components/SpriteRenderer.h"
#include "../Entity.h"
#include <vector>
#include "ColliderManager.h"
#include <SFML/Graphics/Text.hpp>

using std::vector;

//intended to be a singleton
class RenderManager
{
    private:
        RenderManager();
    public:
        vector<SpriteRenderer*> srVector;

        vector<Entity*> listEntity;
        Entity* trackE;
        sf::Text debugConsole;
        bool displayDebugConsole;
        RenderManager(const RenderManager&) = delete;
        RenderManager& operator=(const RenderManager&) = delete;
        sf::RenderWindow window;
        static RenderManager& GetInstance();
        void AddSpriteRenderer(SpriteRenderer* sr);
        void Update();
        sf::IntRect intRect;
        std::string debugText;
        

};

#endif