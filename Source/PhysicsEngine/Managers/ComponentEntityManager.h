


#include "RenderManager.h"
#include "ColliderManager.h"
#include "PhysicsManager.h"

 // Add a component of type T to the entity

template <typename Dst, typename Src>
std::unique_ptr<Dst> unique_dynamic_cast( std::unique_ptr<Src>& ptr ) {
    Src * p = ptr.release();                             // [1]
    std::unique_ptr<Dst> r( dynamic_cast<Dst*>(p) );     // [2]
    if ( !r ) {
        ptr.reset( p );                                  // [3]
    }
    return r;                                            // [4]
}


template <typename T, typename... Args>
T* AddComponent(Entity* _entity, Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    T* component = new T(_entity);
    
    _entity->components[std::type_index(typeid(T))] = component;
    if constexpr (std::is_same<T, SpriteRenderer>::value) {
        RenderManager::GetInstance().AddSpriteRenderer(component);
    }
    else if constexpr (std::is_same<T, BoxCollider>::value)
    {
        ColliderManager::GetInstance().AddCollider(component);
    }
    else if constexpr (std::is_same<T, RigidBody>::value)
    {
        PhysicsManager::GetInstance().rbList.push_back(component);
    }
    return component;
}
template <typename T>
T* GetComponent(Entity* _entity) {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    auto it = _entity->components.find(std::type_index(typeid(T)));
    if (it != _entity->components.end()) {
        return dynamic_cast<T*>(it->second);
    }
    return nullptr;
}

inline void DeleteObjects()
{
    //Delete all Rigidbodies
    for (RigidBody* rb : PhysicsManager::GetInstance().rbList)
    {
        delete rb;
    }
    PhysicsManager::GetInstance().rbList.clear();
    //delete all box colliders
    for (BoxCollider* bc : ColliderManager::GetInstance().colliderVector)
    {
        delete bc;
    }
    ColliderManager::GetInstance().colliderVector.clear();
    //delete all Sprite Renderers
    for (SpriteRenderer* sr : RenderManager::GetInstance().srVector)
    {
        delete sr;
    }
     RenderManager::GetInstance().srVector.clear();
     //delete all entities
     for (Entity* e :  RenderManager::GetInstance().listEntity)
     {
        delete e;
     }
      RenderManager::GetInstance().listEntity.clear();
    delete  RenderManager::GetInstance().trackE;
     RenderManager::GetInstance().trackE = nullptr;

}