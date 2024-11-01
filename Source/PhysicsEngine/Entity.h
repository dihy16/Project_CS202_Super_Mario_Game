#ifndef _entity_h_
#define _entity_h_

#include <memory>
#include <unordered_map>
#include "Component.h"
#include <typeindex>
#include <type_traits>


class Entity
{
    private:
        int id;
        static int nextID;

    public:
        Entity();
        int xPos, yPos;
        float rotation, scaleX, scaleY;
        std::unordered_map<std::type_index, Component*> components;
        
};

#endif //entity_h_
