#ifndef _SpriteRenderer_h_
#define _SpriteRenderer_h_

#include "Component.h"
#include <SFML/Graphics.hpp>


class SpriteRenderer : public Component
{
    private:

    public:
        int layer;
        SpriteRenderer(Entity* _entity);
        sf::Texture texture;
        sf::Sprite sprite;

};

#endif