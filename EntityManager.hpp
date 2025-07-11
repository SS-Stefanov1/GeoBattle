#pragma once

#include "Entity.hpp"

#include <string>
#include <vector>
#include <map>

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager {
	private :
		EntityVec   m_entities;
		EntityVec   m_entitiesToAdd;
		EntityMap   m_entityMap;
		std::size_t m_totalEntities = 0;

		void removeDeadEntities(EntityVec& vec);

	public :
		EntityManager();
		
		void update();

		std::shared_ptr<Entity> addEntity(const std::string& tag);
	
		const EntityVec& getEntities();
		const EntityVec& getEntities(const std::string& tag);
};

