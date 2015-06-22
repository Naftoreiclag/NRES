/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#ifndef NRESSYSTEM_H
#define NRESSYSTEM_H

#include "nresTypedefs.h"
#include "nresEntity.h"

namespace nres {
	class System {
	public:
		System();
		virtual ~System();

		virtual const ComponentID* getComponentIDs(std::size_t& numComponentIDs) const = 0;

		virtual void process(Entity& entity) = 0;
	};
}

#endif // NRESSYSTEM_H
