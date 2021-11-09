#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
#include "Physic.h"

namespace BALL {
	using namespace sf;

	/// <summary>
	/// Создаёт шарик
	/// </summary>
	/// <param name="radius">Радиус шарика</param>
	/// <param name="start_pos">Стартовая позиция шарика</param>
	/// <param name="maxX">Максимальное значение по х</param>
	/// <param name="minX">Минимальное значение по х</param>
	/// <param name="maxY">Максимальное значение по у</param>
	/// <param name="minY">Минимальное значение по у</param>
	/// <param name="obj">Физические объекты</param>
	Ball::Ball(float radius, const Vector2f& start_pos, float maxX, float minX, float maxY, float minY, std::vector<PHYSIC::IPhysicObject*> obj, int n) {
		m_pos = start_pos;
		m_radius = radius;

		max_x = maxX;
		min_x = minX;

		max_y = maxY;
		min_y = minY;

		speed = 0.1f;

		physObj = obj;

		countOfObjects = n;

		update();
	}

	void Ball::move() {
		PHYSIC::Collision collision = hasCollision();

		if (collision.hasCollision) {
			std::cout << "Has collision" << std::endl;
			direction = rebound(direction, collision);
			direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
			std::cout << "New direction: " << direction.x << " " << direction.y << std::endl;
		}

		m_pos += direction * speed;
		update();
	}


	PHYSIC::Collision Ball::hasCollision() {
		PHYSIC::Collision col;
		col.hasCollision = false;
		col.collisionObj = NULL;

		// Проверка по x
		if (!(m_pos.x >= min_x && m_pos.x <= max_x))
			col.hasCollision = true;

		// Проверка по y
		if (!(m_pos.y >= min_y && m_pos.y <= max_y))
			col.hasCollision = true;

		for (auto obj : physObj)
		{
			if (getGlobalBounds().intersects(obj->getCollider().rect)) {
				col.hasCollision = true;
				col.collisionObj = obj;
				break;
			}
		}
		
		return col;
	}


	Vector2f Ball::rebound(const Vector2f& dir, PHYSIC::Collision collision) {
		Vector2f normal = getNormal(collision);
		std::cout << "Normal: " << normal.x << " " << normal.y << std::endl;

		Vector2f reflect;
		if (normal != Vector2f(0, 0))
			reflect = dir - (normal + normal);
		else
			reflect = Vector2f(direction.x, direction.y * -1);
		return reflect;
	}


	Vector2f Ball::getNormal(PHYSIC::Collision collision) {
		// Проверка по x
		if (m_pos.x >= max_x)
			return Vector2f(1, 0);
		if (m_pos.x <= min_x)
			return Vector2f(-1, 0);

		// Проверка по y
		if (m_pos.y >= max_y)
			return Vector2f(0, 1);
		if (m_pos.y <= min_y)
			return Vector2f(0, -1);

		PHYSIC::Collider collider = collision.collisionObj->getCollider();
			
		// Столкновение сверху
		if (m_pos.y <= collider.rect.top) {
			std::cout << "Collision on top physic object!!" << std::endl;
			return Vector2f(0, 1);
		}

		// Столкновение снизу
		if (m_pos.y >= collider.rect.top - collider.rect.height) {
			std::cout << "Collision on bottom of physic object!!!" << std::endl;
			return Vector2f(0, -1);
		}
		

		return Vector2f(0, 0);
	}


	void Ball::setDirection(const Vector2f& dir) {
		direction = dir;
	}

	
	std::size_t Ball::getPointCount() const {
		return 30;
	}


	Vector2f Ball::getPoint(std::size_t index) const {
		static const float pi = 3.141592654f;

		float angle = index * 2 * pi / getPointCount();
		float x = std::cos(angle) * m_radius + m_pos.x;
		float y = std::sin(angle) * m_radius + m_pos.y;

		return sf::Vector2f(x, y);
	}
}