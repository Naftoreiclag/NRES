/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#include "nresEntity.h"

#include <cassert>
#include <vector>
#include "nresWorld.h"

namespace nres {

	Entity::Entity(World& world)
	: world(world),
	finalized(false) {
	}

	Entity::~Entity() {
		for(std::map<ComponentID, ComponentData*>::iterator it = componentDataMap.begin(); it != componentDataMap.end(); ++ it) {
			delete it->second;
		}
	}

	void Entity::addComponent(const ComponentID& compID, ComponentData* data) {
		assert(!finalized);

		// If this component already exists in entity, then overwrite it
		std::map<ComponentID, ComponentData*>::iterator overwrite = componentDataMap.find(compID);
		if(overwrite != componentDataMap.end()) {
            componentDataMap.erase(overwrite);
		}

		componentDataMap.insert(std::pair<ComponentID, ComponentData*>(compID, data));
	}

	void Entity::finalize() {
		assert(!finalized);

		// Iterate over all pairs
		for(std::map<ComponentID, ComponentData*>::iterator it = componentDataMap.begin(); it != componentDataMap.end(); ++ it) {
			// Tell the world that this has certain components
			ComponentID compID = it->first;
			world.knownEntitiesByComponents.add(compID, this);
		}

		finalized = true;
	}


	ComponentData* Entity::getComponentData(const ComponentID& compID) {

		std::map<ComponentID, ComponentData*>::iterator location = componentDataMap.find(compID);

		if(location == componentDataMap.end()) {
			return 0;
		}

		return location->second;
	}

	void Entity::deleteSelf() {
		world.deleteEntity(this);
	}

    Entity& Entity::duplicate() {
		Entity& clone = world.newEntity();

		for(std::map<ComponentID, ComponentData*>::iterator it = componentDataMap.begin(); it != componentDataMap.end(); ++ it) {
			clone.addComponent(it->first, it->second->clone());
		}

		if(finalized) {
			clone.finalize();
		}

		return clone;
    }
}


