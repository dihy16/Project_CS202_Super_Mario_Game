#ifndef _boxcollider_h_
#define _boxcollider_h_

#include "Component.h"
#include "../Entity.h"
#include <functional>

class BoxCollider : public Component{

public:
    BoxCollider(Entity* _entity);
    float width, height;
    std::function<void(BoxCollider*)> OnCollisionEnter, OnCollisionStay, OnCollisionExit;
    bool OverlayWith(BoxCollider* collider);

};

#endif