/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */
#ifndef NRES_WORLD_HPP
#define NRES_WORLD_HPP

#include <vector>

#include "nresSystem.hpp"
#include "nresEntity.hpp"

namespace nres
{

class World {
public:
    World();
    ~World();
private:
    std::vector<System*> systems;

public:
    void attachSystem(System* system);
    
    Entity* newEntity();
    void deleteEntity(Entity* entity);
    
    friend class Entity;
};

}

#endif // NRES_WORLD_HPP
