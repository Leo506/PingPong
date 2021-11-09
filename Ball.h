#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Physic.h"

namespace BALL {
	using namespace sf;
	class Ball : public Shape {
	public:
		Ball(float radius, const Vector2f& start_pos, float maxX, float minX, float maxY, float minY, std::vector<PHYSIC::IPhysicObject*> obj, int n);
		void move();
		void setDirection(const Vector2f& dir);
		virtual std::size_t getPointCount() const;
		virtual Vector2f getPoint(std::size_t index) const;

	private:
		PHYSIC::Collision hasCollision();
		Vector2f rebound(const Vector2f& dir, PHYSIC::Collision);
		Vector2f getNormal(PHYSIC::Collision);

		float m_radius;
		Vector2f m_pos;

		float max_x;
		float min_x;

		float max_y;
		float min_y;

		Vector2f direction;

		float speed;

		std::vector<PHYSIC::IPhysicObject*> physObj;
		int countOfObjects;
	};
}