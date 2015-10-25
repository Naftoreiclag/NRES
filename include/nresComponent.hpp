/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */
#ifndef NRES_COMPONENT_HPP
#define NRES_COMPONENT_HPP

#include "nresTypedefs.hpp"

namespace nres
{

class Component
{
public:
    Component();
    virtual ~Component();
public:
    virtual const ComponentID& getID() = 0;
};

}

#endif // NRES_COMPONENT_HPP
