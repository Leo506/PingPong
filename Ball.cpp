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
	Ball::Ball(float radius, const Vector2f& start_pos, float maxX, float minX, float maxY, float minY, PHYSIC::IPhysicObject* obj, int n) {
		circle.setRadius(radius);
		circle.setPosition(start_pos);
		circle.setFillColor(Color::Red);

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
		if (hasCollision()) {
			std::cout << "Has collision" << std::endl;
			direction = rebound(direction);
			direction /= std::sqrt(direction.x * direction.x + direction.y * direction.y);
			std::cout << "New direction: " << direction.x << " " << direction.y << std::endl;
		}

		circle.move(direction * speed);
		update();
	}


	bool Ball::hasCollision() {

		// Проверка по x
		if (!(circle.getPosition().x >= min_x && circle.getPosition().x <= max_x))
			return true;

		// Проверка по y
		if (!(circle.getPosition().y >= min_y && circle.getPosition().y <= max_y))
			return true;

		for (int i = 0; i < countOfObjects; i++)
		{
			if (circle.getGlobalBounds().intersects(physObj[i].getCollider().rect))
				return true;
		}
		
		return false;
	}


	Vector2f Ball::rebound(const Vector2f& dir) {
		Vector2f normal = getNormal();
		std::cout << "Normal: " << normal.x << " " << normal.y << std::endl;

		Vector2f reflect;
		if (normal != Vector2f(0, 0))
			reflect = dir - (normal + normal);
		else
			reflect = Vector2f(direction.x, direction.y * -1);
		return reflect;
	}


	Vector2f Ball::getNormal() {
		// Проверка по x
		if (circle.getPosition().x >= max_x)
			return Vector2f(1, 0);
		if (circle.getPosition().x <= min_x)
			return Vector2f(-1, 0);

		// Проверка по y
		if (circle.getPosition().y >= max_y)
			return Vector2f(0, 1);
		if (circle.getPosition().y <= min_y)
			return Vector2f(0, -1);

		for (int i = 0; i < countOfObjects; i++)
		{
			PHYSIC::Collider collider = physObj[i].getCollider();
			
			// Столкновение сверху
			if (circle.getPosition().y <= collider.rect.top) {
				std::cout << "Collision on top physic object!!" << std::endl;
				return Vector2f(0, 1);
			}

			// Столкновение снизу
			if (circle.getPosition().y >= collider.rect.top - collider.rect.height) {
				std::cout << "Collision on bottom of physic object!!!" << std::endl;
				return Vector2f(0, -1);
			}
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
		float x = std::cos(angle) * circle.getRadius() + circle.getPosition().x;
		float y = std::sin(angle) * circle.getRadius() + circle.getPosition().y;

		return sf::Vector2f(x, y);
	}
}