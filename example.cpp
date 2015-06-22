#include <iostream>

#include "NREntitySystem.h"

nres::ComponentID positionID = 0;
nres::ComponentID velocityID = 1;

class PositionComponentData : public nres::ComponentData {
public:
	int x;

	PositionComponentData(int initialValue) {
		x = initialValue;
	}

	virtual PositionComponentData* clone() const {
		return new PositionComponentData(x);
	}

	virtual ~PositionComponentData() {}
};

class VelocityComponentData : public nres::ComponentData {
public:
	int v;

	VelocityComponentData(int initialValue) {
		v = initialValue;
	}

	virtual VelocityComponentData* clone() const {
		return new VelocityComponentData(v);
	}

	virtual ~VelocityComponentData() {}
};

class PhysicsSystem : public nres::System {
public:
	nres::ComponentID componentIDs[2];

	PhysicsSystem() {
		componentIDs[0] = positionID;
		componentIDs[1] = velocityID;
	}
	virtual ~PhysicsSystem() {}

	virtual const nres::ComponentID* getComponentIDs(std::size_t& numComponentIDs) const {
		numComponentIDs = 2;
		return componentIDs;
	}

	virtual void process(nres::Entity& entity) {
		PositionComponentData* position = (PositionComponentData*) entity.getComponentData(positionID);
		VelocityComponentData* velocity = (VelocityComponentData*) entity.getComponentData(velocityID);

		position->x += velocity->v;
	}
};


int main() {
	std::cout << "positionID = " << positionID << std::endl;
	std::cout << "velocityID = " << velocityID << std::endl;

	nres::World world;

	PhysicsSystem physicsSys;

	nres::Entity& entity = world.newEntity();
	entity.addComponent(positionID, new PositionComponentData(0));
	entity.addComponent(velocityID, new VelocityComponentData(1));
	entity.finalize();

	nres::Entity& duplicate = entity.duplicate();
	((VelocityComponentData*) duplicate.getComponentData(velocityID))->v = -5;

	bool running = true;
	while(running) {
		world.process(physicsSys);

		std::cout << "x1: " << ((PositionComponentData*) entity.getComponentData(positionID))->x;
		std::cout << " v1: " << ((VelocityComponentData*) entity.getComponentData(velocityID))->v;
		std::cout << "\tx2: " << ((PositionComponentData*) duplicate.getComponentData(positionID))->x;
		std::cout << " v2: " << ((VelocityComponentData*) duplicate.getComponentData(velocityID))->v;
		std::cout << std::endl;
	}

	return 0;
}
