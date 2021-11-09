#pragma once
#include <SFML/Graphics.hpp>
namespace PHYSIC {

	struct Collider {
		sf::FloatRect rect;
	};

	class IPhysicObject {
	public:
		virtual Collider getCollider() = 0;
	};

	struct Collision {
		bool hasCollision;
		IPhysicObject* collisionObj = NULL;
	};
}