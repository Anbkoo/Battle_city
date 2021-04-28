#include "Container.h"

void Entity::addGroup(Group _group) {
	groupBitSet[_group] = true;
	manager.addToGroup(this, _group);
}
