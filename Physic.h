#pragma once
#include <SFML/Graphics.hpp>
namespace PHYSIC {

	struct Collider {
		sf::Vector2f pos;
		sf::Vector2f size;
	};

	class IPhysicObject {
	public:
		virtual Collider getCollider() = 0;
	};
}