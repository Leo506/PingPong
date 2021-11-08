#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Physic.h"

namespace BLOCK {
	class PlayerBlock : public sf::Shape, public PHYSIC::IPhysicObject{
	public:
		void move(const sf::Vector2f&);
		sf::Vector2f rebound(const sf::Vector2f&);
		PlayerBlock(sf::Vector2f, sf::Vector2f, float, float);

		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
		virtual PHYSIC::Collider getCollider();

	private:
		bool validMove(const sf::Vector2f&);
		sf::RectangleShape rectangle;
		float max_x;
		float min_x;

		PHYSIC::Collider collider;
	};
}

#endif // !BLOCK_H
