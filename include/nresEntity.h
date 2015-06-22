/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#ifndef NRESENTITY_H
#define NRESENTITY_H

#include <map>

#include "nresTypedefs.h"
#include "nresComponentData.h"

namespace nres {
	class World;
	class Entity {
	public:
		friend class World;

		World& world;

		void addComponent(const ComponentID& compID, ComponentData* data);
		void removeComponent(const ComponentID& compID);
		ComponentData* getComponentData(const ComponentID& compID);

		// Publish component signature to world
		void finalize();
		void deleteSelf(); // world.deleteEntity(this);

		// Creates a copy of this entity, its component signature, whether or not it is finalized, and all component data; registers copy with world as new entity
		Entity& duplicate();
	private:
		bool finalized;
		std::map<ComponentID, ComponentData*> componentDataMap;
		Entity(World& world);
		~Entity();
	};
}

#endif // NRESENTITY_H
