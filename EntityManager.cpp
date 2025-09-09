#include "EntityManager.hpp"

EntityManager::EntityManager() {};

void EntityManager::removeDeadEntities(EntityVec& v) {
	v.erase( std::remove_if(v.begin(), v.end(),[](const std::shared_ptr<Entity>& e) { return !e->isActive(); }), v.end() );
};

void EntityManager::update() {
	for (auto& e : m_entitiesToAdd) {
		m_entities.push_back(e);
	}

	m_entitiesToAdd.clear();

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

EntityVec EntityManager::getEntities(const std::string& tag) {
	if (tag == "all") { return m_entities; }

	static EntityVec entities;
	entities.clear();

	for (auto& e : m_entities) {
		if (e->tag() == tag) { entities.push_back(e); }
	}

	return entities;
};