/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#ifndef NRESWORLD_H
#define NRESWORLD_H

#include "nresSystem.h"
#include <vector>
#include <map>

#include "nresMapOfSets.h"

namespace nres {
	class World {
	public:
		friend class Entity;
		World();
		virtual ~World();


		// The creation and deletion of all entities is handled by the world, since all entities are tied to their world
		Entity& newEntity();
		void deleteEntity(Entity* entity);
		const std::vector<Entity*>& getAllEntities() const;

		void process(System& system);
	private:
		// All entities created by newEntity(); includes all unfinalized and component-less enities; unsorted
		std::vector<Entity*> knownEntities;

		// Entities by component
		MapOfSets<ComponentID, Entity*> knownEntitiesByComponents;
	};
}

#endif // NRESWORLD_H
