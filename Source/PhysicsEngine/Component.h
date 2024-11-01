#ifndef _component_h_
#define _component_h_
class Entity;

class Component
{   
    protected:
        bool isActive;
        Entity* owner;

    public:
        Entity* GetOwner();
        Component(Entity* _entity);
        bool GetActive();
        void SetActive(bool _isActive);

};

#endif