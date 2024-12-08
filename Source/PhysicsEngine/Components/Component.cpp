#include "Component.h"

Component::Component(Entity* _entity)
{
    isActive = true;
   owner = _entity;
}

Entity* Component::GetOwner()
{
    return owner;
}

bool Component::GetActive()
{
    return isActive;
}

void Component::SetActive(bool _isActive)
{
    isActive = _isActive;
}