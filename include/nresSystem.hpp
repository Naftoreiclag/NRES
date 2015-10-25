/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */
#ifndef NRES_SYSTEM_HPP
#define NRES_SYSTEM_HPP

#include "nresTypedefs.hpp"
#include "nresEntity.hpp"

#include <vector>

namespace nres
{

class System {
public:
    System();
    virtual ~System();
public:
    virtual void onEntityExists(Entity* entity) = 0;
    virtual void onEntityDestroyed(Entity* entity) = 0;
    virtual void onEntityBroadcast(Entity* entity, void* data) = 0;
    
    virtual const std::vector<ComponentID>& getRequiredComponents() = 0;
};

}

#endif // NRES_SYSTEM_HPP
