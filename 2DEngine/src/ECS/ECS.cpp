#include "ECS.h"

void Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true;
	manager.AddToGRoup(this, mGroup);
}