/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */
#include "nresEntity.hpp"

#include <cassert>

#include "nresWorld.hpp"
#include "nresComponent.hpp"

namespace nres
{

Entity::Entity(World* world)
: world(world)
, isPublished(false) {
}

Entity::~Entity()
{
}


void Entity::add(Component* component) {
    assert(!isPublished);
    
    components.push_back(component);
}

void Entity::publish() {
    assert(!isPublished);
    isPublished = true;
    
    for(std::vector<System*>::iterator sysIter = world->systems.begin(); sysIter != world->systems.end(); ++ sysIter) {
        System* sys = *sysIter;
        
        if(true) {
            systems.push_back(sys);
            sys->onEntityExists(this);
        }
    }
}

Component* Entity::getComponent(const ComponentID& componentID) {
    assert(isPublished);
    
    for(std::vector<Component*>::iterator compIter = components.begin(); compIter != components.end(); ++ compIter) {
        Component* comp = *compIter;
        
        if(comp->getID() == componentID) {
            return comp;
        }
    }
    
    return 0;
}

void Entity::broadcast(void* data) {
    assert(isPublished);
    
    for(std::vector<System*>::iterator sysIter = systems.begin(); sysIter != systems.end(); ++ sysIter) {
        System* sys = *sysIter;
        
        sys->onEntityBroadcast(this, data);
    }
}

}

