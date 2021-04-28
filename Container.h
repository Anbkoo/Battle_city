#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <array>
#include <bitset>

class Container_Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	//static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Container_Component*, maxComponents>;

class Container_Component {
public:
	Entity *entity;

	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};

	virtual ~Container_Component() {};
};

class Entity {
public:
	Entity(Manager& _manager) : manager(_manager) {};

	void update() {
		for (const auto& v : components)
			v->update();
	};
	void draw() {
		for (const auto& v : components)
			v->draw();
	};
	bool isActive() const {
		return active;
	}

	bool hasGroup(Group _group) {
		return groupBitSet[_group];
	}

	void addGroup(Group _group);

	void delGroup(Group _group) {
		groupBitSet[_group] = false;
	}

	void destroy() {
		active = false;
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... _args)
	{
		T* v(new T(std::forward<TArgs>(_args)...));
		v->entity = this;
		std::unique_ptr<Container_Component>uPtr{ v };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = v;
		componentBitSet[getComponentTypeID<T>()] = true;

		v->init();
		return *v;
	}

	template <typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	bool active = true;
	std::vector<std::unique_ptr<Container_Component>> components;

	Manager& manager;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};

class Manager {
public:
	void update() {
		for (const auto& v : entities)
			v->update();
	};
	void draw() {
		for (const auto& v : entities)
			v->draw();
	};

	void refresh() {
		for (auto i(0u); i < maxGroups; i++) {
			auto& v(group_Entities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v),
				[i](Entity* _entity) {
				return !_entity->isActive() || _entity->hasGroup(i);
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &_entity) {
			return !_entity->isActive();
		}),
			std::end(entities));
	}

	Entity& addEntity() {
		Entity* ent = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ ent };
		entities.emplace_back(std::move(uPtr));
		return *ent;
	}

	void addToGroup(Entity* _entity, Group _group) {
		group_Entities[_group].emplace_back(_entity);
	}

	std::vector<Entity*>& getGroup(Group _group) {
		return group_Entities[_group];
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> group_Entities;
};
