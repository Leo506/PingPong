#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
#include "Physic.h"
#include "Block.h"
#include "UI.h"

namespace BALL {
	using namespace sf;

	/// <summary>
	/// Создаёт шарик
	/// </summary>
	/// <param name="radius">Радиус</param>
	/// <param name="start_pos">Стартовая позиция</param>
	/// <param name="maxX">Максимальное значение по x</param>
	/// <param name="minX">Минимальное значение по x</param>
	/// <param name="maxY">Максимальное значение по y</param>
	/// <param name="minY">Минимальное значение по y</param>
	/// <param name="obj">Вектор физических объектов</param>
	Ball::Ball(float radius, const Vector2f& start_pos, float maxX, float minX, float maxY, float minY, std::vector<PHYSIC::IPhysicObject*>* obj, GAME::GameController* gameController) {
		m_pos = start_pos;
		m_radius = radius;

		max_x = maxX;
		min_x = minX;

		max_y = maxY;
		min_y = minY;

		speed = 0.15f;

		physObj = obj;

		pGameController = gameController;

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

		// Проверка y
		if (!(m_pos.y >= min_y && m_pos.y <= max_y))
			col.hasCollision = true;

		for (int i = 0; i < physObj->size(); i++)
		{
			if (getGlobalBounds().intersects((*physObj)[i]->getCollider().rect)) {
				col.hasCollision = true;
				col.collisionObj = (*physObj)[i];

				BLOCK::DestoyingBlock* destBlock = dynamic_cast<BLOCK::DestoyingBlock*>((*physObj)[i]);
				if (destBlock != NULL) {
					destBlock->getDamage(10);
				}

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
		// Проверка x
		if (m_pos.x >= max_x)
			return Vector2f(1, 0);
		if (m_pos.x <= min_x)
			return Vector2f(-1, 0);

		// Проверка y
		if (m_pos.y >= max_y) {
			pGameController->getDamage();
			return Vector2f(0, 1);
		}
		if (m_pos.y <= min_y)
			return Vector2f(0, -1);

		PHYSIC::Collider collider = collision.collisionObj->getCollider();

			
		// Столкновение сверху
		if (m_pos.y <= collider.rect.top) {
			std::cout << "Collision on top physic object!!" << std::endl;
			if (m_pos.x <= collider.rect.left + collider.rect.width / 2)
				return Vector2f(0.5f, 0.5f);
			else
				return Vector2f(-0.5f, 0.5f);
		}

		// Столкновение снизу
		if (m_pos.y >= collider.rect.top - collider.rect.height) {
			std::cout << "Collision on bottom of physic object!!!" << std::endl;
			return Vector2f(0, -1);
		}

		if (m_pos.x >= collider.rect.left) {
			std::cout << "Collision on left of physic object!!!" << std::endl;
			return Vector2f(1, 0);
		}

		if (m_pos.x <= collider.rect.left + collider.rect.width) {
			std::cout << "Collision on right of physic object!!!" << std::endl;
			return Vector2f(-1, 0);
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