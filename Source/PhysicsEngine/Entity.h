#ifndef _entity_h_
#define _entity_h_

#include <memory>
#include <unordered_map>
#include "Components/Component.h"
#include <typeindex>
#include <type_traits>
#include <string>

class Entity
{
private:
    int id;
    static int nextID;

public:
    Entity();
    float xPos, yPos;
    float xOrigin, yOrigin;
    std::string name, tag;
    float rotation, scaleX, scaleY;
    std::unordered_map<std::type_index, Component *> components;
    int getID();
};

#endif // entity_h_
