#include "EntityManager.hpp"

EntityManager::EntityManager() {};

void EntityManager::removeDeadEntities(EntityVec& v) {
	
};

void EntityManager::update() {
	m_entitiesToAdd.clear();

	for (auto& e : m_entitiesToAdd) {
		m_entities.push_back(e);
	}

	removeDeadEntities(m_entities);

	for (auto& [tag, entityVec] : m_entityMap) {
		removeDeadEntities(entityVec);
	}
};


std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
	m_entitiesToAdd.push_back(entity);

	return entity;
};

const EntityVec& EntityManager::getEntities() {
	return m_entities;
};

const EntityVec& EntityManager::getEntities(const std::string& tag) {
	return m_entities;
};