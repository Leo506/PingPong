#pragma once


#include <SFML/Graphics.hpp>
#include "Physic.h"
#include "Reset.h"

namespace BLOCK {
	class PlayerBlock : public sf::Shape, public PHYSIC::IPhysicObject, public RESET::IResetableObject{
	public:
		void move(const sf::Vector2f&);
		sf::Vector2f rebound(const sf::Vector2f&);
		PlayerBlock(sf::Vector2f, sf::Vector2f, float, float);

		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
		virtual PHYSIC::Collider getCollider();
		virtual void reset();

		~PlayerBlock() {};

	private:
		bool validMove(const sf::Vector2f&);
		float max_x;
		float min_x;

		sf::Vector2f m_pos;
		sf::Vector2f m_size;

		PHYSIC::Collider collider;
	};


	class DestoyingBlock : public sf::Shape, public PHYSIC::IPhysicObject {
	public:
		DestoyingBlock(sf::Vector2f pos, sf::Vector2f size, float hp);
		void getDamage(float value);
		float getHP() { return m_hp; }

		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
		virtual PHYSIC::Collider getCollider();

		~DestoyingBlock() {};

	private:
		float m_hp;
		sf::Vector2f m_pos;
		sf::Vector2f m_size;

		PHYSIC::Collider m_collider;
	};
}


