/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#include "nresWorld.h"

#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

namespace nres {

	World::World()
	{

	}

	World::~World() {
		for(std::vector<Entity*>::iterator it = knownEntities.begin(); it != knownEntities.end(); ++ it) {
			delete *it;
		}
	}

	void World::process(System& system) {
		unsigned int numComps = 0;
		const ComponentID* accessedComponents = system.getComponentIDs(numComps);

		// System processes no components
		if(numComps == 0) {
			return;
		}

		// System processes exactly one component
		if(numComps == 1) {
			ComponentID compID = *accessedComponents;
			if(!knownEntitiesByComponents.hasKey(compID)) {
				return;
			}

			std::set<Entity*>* appliedEntities = knownEntitiesByComponents.getSet(compID);

			for(std::set<Entity*>::iterator it = appliedEntities->begin(); it != appliedEntities->end(); ++ it) {
				Entity& processMe = **it;

				system.process(processMe);
			}
		}

		// System processes exactly two components, use stl intersection
		else if(numComps == 2) {

			ComponentID compAID = *accessedComponents;
			if(!knownEntitiesByComponents.hasKey(compAID)) {
				return;
			}
			ComponentID compBID = *(accessedComponents + 1);
			if(!knownEntitiesByComponents.hasKey(compBID)) {
				return;
			}

			std::set<Entity*>* entitySetA = knownEntitiesByComponents.getSet(compAID);
			std::set<Entity*>* entitySetB = knownEntitiesByComponents.getSet(compBID);

			std::vector<Entity*> appliedEntities;

			std::set_intersection(entitySetA->begin(), entitySetA->end(),
									entitySetB->begin(), entitySetB->end(),
									std::back_inserter(appliedEntities));

			for(std::vector<Entity*>::iterator it = appliedEntities.begin(); it != appliedEntities.end(); ++ it) {
				Entity& processMe = **it;

				system.process(processMe);
			}
		}

		// System processes >2 components
		else {
			// If any component has no entity, then do nothing; Also find the smallest set of entities and store the sets in an array
			std::set<Entity*>* allSets[numComps];
			std::set<Entity*>* smallestSet = 0;
			std::size_t smallestSetSize;
            for(std::size_t i = 0; i < numComps; ++ i) {
				ComponentID compID = *(accessedComponents + i);

				std::set<Entity*>* entitiesWithComp = knownEntitiesByComponents.getSet(compID);

				if(!smallestSet) {
					smallestSet = entitiesWithComp;
				} else {
					if(smallestSetSize > entitiesWithComp->size()) {

						// If any set has no elements, then return
						if(entitiesWithComp->size() == 0) {
							return;
						}

						smallestSetSize = entitiesWithComp->size();
						smallestSet = entitiesWithComp;
					}
				}

				allSets[i] = entitiesWithComp;
            }

            // Where to store the intersection
            std::vector<Entity*> intersection;

			// Compare all elements of the smallest set with the elements of all other sets, keeping those which are present in every one
			for(std::set<Entity*>::iterator it = smallestSet->begin(); it != smallestSet->end(); ++ it) {

				Entity* checkMe = *it;
				bool missing = false;
				for(unsigned int i = 0; i < numComps; ++ i) {
					std::set<Entity*>* entitiesWithComp = allSets[i];

					// No need to compare the smallest set with itself
					if(entitiesWithComp != smallestSet) {

						// If the element is absent in this set, then stop searching
						if(entitiesWithComp->find(checkMe) == entitiesWithComp->end()) {
							missing = true;
							break;
						}
					}
				}

				// If it was present in all sets, then add it to the intersection
				if(!missing) {
					intersection.push_back(checkMe);
				}
			}

			// Usual processing
			for(std::vector<Entity*>::iterator it = intersection.begin(); it != intersection.end(); ++ it) {
				Entity& processMe = **it;

				system.process(processMe);
			}
		}
	}

	Entity& World::newEntity() {
		Entity* newEnt = new Entity(*this);

		knownEntities.push_back(newEnt);

		return *newEnt;
	}

	void World::deleteEntity(Entity* entity) {
		knownEntities.erase(std::remove(knownEntities.begin(), knownEntities.end(), entity), knownEntities.end());
		//knownEntitiesByComponents.removeValueEntirely(entity);

		delete entity;
	}

	const std::vector<Entity*>& World::getAllEntities() const {
        return knownEntities;
	}
}


