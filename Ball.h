#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Physic.h"
#include "Reset.h"
#include "Game.h"

namespace BALL {
	class Ball : public sf::Shape, public RESET::IResetableObject {
	public:
		Ball(float radius, const sf::Vector2f& start_pos, float maxX, float minX, float maxY, float minY, std::vector<PHYSIC::IPhysicObject*>* obj, GAME::GameController* gameController);
		void move();
		void setDirection(const sf::Vector2f& dir);
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
		virtual void reset();

	private:
		PHYSIC::Collision hasCollision();
		sf::Vector2f rebound(const sf::Vector2f& dir, PHYSIC::Collision);
		sf::Vector2f getNormal(PHYSIC::Collision);

		float m_radius;
		sf::Vector2f m_pos;

		float max_x;
		float min_x;

		float max_y;
		float min_y;

		sf::Vector2f direction;

		float speed;

		std::vector<PHYSIC::IPhysicObject*>* physObj;
		GAME::GameController* pGameController;
	};
}