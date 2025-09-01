#pragma once

#include "Components.hpp"
#include <memory>
#include <string>

class Entity {
	friend class EntityManager;

	private :
		bool m_active     = true;
		std::size_t m_id  = 0;
		std::string m_tag = "default";

		Entity(const std::size_t id, const std::string& tag);

	public : 
		std::shared_ptr<CTransform> cTransform;
		std::shared_ptr<CShape>     cShape;
		std::shared_ptr<CBullet>    cBullet;
		std::shared_ptr<CCollision> cCollision;
		std::shared_ptr<CInput>     cInput;
		std::shared_ptr<CScore>     cScore;
		std::shared_ptr<CLifespan>  cLifespan;

		bool isActive() const;
		const std::string& tag() const;
		const std::size_t id() const;
		void destroy();
};

