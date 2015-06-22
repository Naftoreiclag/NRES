/* Copyright (c) 2015 "Naftoreiclag" https://github.com/Naftoreiclag
 *
 * Distributed under the Apache License Version 2.0 (http://www.apache.org/licenses/)
 * See accompanying file LICENSE
 */

#ifndef NRESCOMPONENTDATA_H
#define NRESCOMPONENTDATA_H

namespace nres {
class ComponentData {
public:
	ComponentData();
	virtual ComponentData* clone() const = 0;
	virtual ~ComponentData();
};
}

#endif // NRESCOMPONENTDATA_H
