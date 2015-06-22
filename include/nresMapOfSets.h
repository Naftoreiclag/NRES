/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#ifndef NRESMAPOFSETS_H
#define NRESMAPOFSETS_H

#include <map>
#include <set>
#include <algorithm>

namespace nres {
	template<typename K, typename V> class MapOfSets
	{
	public:
		MapOfSets() {}
		~MapOfSets() {
			for(typename std::map<K, std::set<V>* >::iterator location = data.begin(); location != data.end(); ++ location) {
				std::set<V>* takeOut = location->second;

				delete takeOut;
			}
		}

		std::map<K, std::set<V>* > data;
	public:
		// getReady, ______, Go!
		std::set<V>* getSet(const K key) const {
			typename std::map<K, std::set<V>* >::const_iterator location = data.find(key);
			if(location == data.end()) {
				return 0;
			} else {
				return location->second;
			}
		}
		// Add value to the set named by key, creating it if it does not exist
		void add(const K key, const V value) {
			// Get the set to store the value into, creating it if it does not exist
			std::set<V>* putInto;
			typename std::map<K, std::set<V>* >::iterator location = data.find(key);
			if(location == data.end()) {
				putInto = new std::set<V>();
				data[key] = putInto;
			} else {
				putInto = location->second;
			}

			// Add the new value
			putInto->insert(value);
		}
		// Remove value from the set named by key, deleting the set and removing the key if it is now empty
		void removePair(const K key, const V value) {
			// Find the set associated with the key
			std::set<V>* takeOut;
			typename std::map<K, std::set<V>* >::iterator location = data.find(key);
			if(location == data.end()) {
				return; // If the key did not exist, do nothing
			}
			takeOut = location->second;
			takeOut->erase(std::remove(takeOut->begin(), takeOut->end(), value), takeOut->end());

			// If the set is now completely empty, remove the key and delete set
			if(takeOut->empty()) {
				delete takeOut;
				data.erase(location);
			}
		}
		// Remove from all sets this value
		void removeValueEntirely(const V value) {
			for(typename std::map<K, std::set<V>* >::iterator location = data.begin(); location != data.end(); ++ location) {
				std::set<V>* takeOut = location->second;

				takeOut->erase(std::remove(takeOut->begin(), takeOut->end(), value), takeOut->end());
				if(takeOut->empty()) {
					delete takeOut;
					data.erase(location);
				}
			}
		}
		// Remove key and delete set if it exists
		void removeKey(const K key) {
			// Find the set associated with the key
			std::set<V>* deleteMe;
			typename std::map<K, std::set<V>* >::iterator location = data.find(key);
			if(location == data.end()) {
				return; // If the key did not exist, do nothing
			}
			deleteMe = location->second;

			delete deleteMe; // delete set
			data.erase(location); // remove key
		}
		// Returns true if there is a set with >0 elements named by key
		bool hasKey(const K key) {
			typename std::map<K, std::set<V>* >::iterator location = data.find(key);
			return location != data.end();
		}
		// Returns number of keys, which is also the number of sets with >0 elements
		std::size_t numKeys(const K key) {
			typename std::map<K, std::set<V>* >::iterator location = data.find(key);
			if(location == data.end()) {
				return 0;
			} else {
				return location->second->size();
			}
		}
	};
}

#endif // NRESMAPOFSETS_H
