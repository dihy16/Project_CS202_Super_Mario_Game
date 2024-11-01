#ifndef _RenderManager_h_
#define _RenderManager_h_
#include "SpriteRenderer.h"
#include "Entity.h"
#include <vector>

using std::vector;

//intended to be a singleton
class RenderManager
{
    private:
        RenderManager();
        vector<SpriteRenderer*> srVector;
    public:
        Entity* trackE;

        RenderManager(const RenderManager&) = delete;
        RenderManager& operator=(const RenderManager&) = delete;
        sf::RenderWindow window;
        static RenderManager& GetInstance();
        void AddSpriteRenderer(SpriteRenderer* sr);
        void Update();
        

};

#endif