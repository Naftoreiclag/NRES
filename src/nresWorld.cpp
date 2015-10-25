/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */
#include "nresWorld.hpp"

namespace nres
{

World::World()
{
}

World::~World()
{
}

void World::attachSystem(System* system) {
    systems.push_back(system);
}

Entity* World::newEntity() {
    return new Entity(this);
}

void World::deleteEntity(Entity* entity) {
    delete entity;
}


}

