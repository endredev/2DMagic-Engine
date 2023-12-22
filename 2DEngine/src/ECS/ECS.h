#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID() {
	static ComponentID lastId = 0u;
	return lastId++;
}

template <typename T> 
inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
	Entity* entity;
	
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity {
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitSet groupBitset;
public:
	Entity(Manager& mMeneger) : manager(mMeneger) {}
	void Update() {
		for (auto& component : components) {
			component->Update();
		}
	}
	void Draw() {
		for (auto& component : components) {
			component->Draw();
		}
	}
	bool IsActive() { return active; }
	void Destroy() { active = false; }

	template <typename T>
	bool hasComponent() const {
		return componentBitset[getComponentTypeID<T>()];
	};

	bool hasGroup(Group mGroup) {
		return groupBitset[mGroup];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* component(new T(std::forward<TArgs>(mArgs)...));
		component->entity = this;
		std::unique_ptr<Component> uPtr(component);
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = component;
		componentBitset[getComponentTypeID<T>()] = true; 

		component->Init();
		return *component;
	}

	void addGroup(Group mGroup);

	void delGroup(Group mGroup) {
		groupBitset[mGroup] = false;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager {
public:
	void Update() {
		for (auto& entity : entities) {
			entity->Update();
		}
	}

	void Draw() {
		for (auto& entity : entities) {
			entity->Draw();
		}
	}

	void Refresh() {
		for (auto i(0u); i < maxGroups; i++) {
			auto& v(groupEntities[i]); // todo
			v.erase(std::remove_if(
				std::begin(v), 
				std::end(v), 
				[i](Entity* mEntity) {
					return !mEntity->IsActive() || !mEntity->hasGroup(i);
				}),
				std::end(v));
		}

		entities.erase(std::remove_if(
			std::begin(entities),
			std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity) {
				return !mEntity->IsActive();
			}),
			std::end(entities));
	}

	void AddToGRoup(Entity* mEntity, Group mGroup) {
		groupEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		return groupEntities[mGroup];
	}

	Entity& addEntity() {
		Entity* entity = new Entity(*this);
		std::unique_ptr<Entity> uPtr(entity);
		entities.emplace_back(std::move(uPtr));

		return *entity;
	}
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupEntities;
};