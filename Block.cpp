#include "Block.h"
#include <SFML/Graphics.hpp>
#include "Physic.h"

namespace BLOCK {
	using namespace sf;

	/// <summary>
	/// Инициализирует блок, которым управляет игрок
	/// </summary>
	/// <param name="size">Размер блока</param>
	/// <param name="pos">Позиция блока</param>
	/// <param name="maxX">Максимальное значение по х</param>
	/// <param name="minX">Минимальное значение по х</param>
	PlayerBlock::PlayerBlock(Vector2f size, Vector2f pos, float maxX, float minX) {
		rectangle.setSize(size);
		rectangle.setPosition(pos);
		rectangle.setFillColor(Color::White);

		min_x = minX + size.x / 2;
		max_x = maxX - size.x / 2;

		collider.pos = pos;
		collider.size = Vector2f(size.x / 2, size.y / 2);

		update();
	}


	void PlayerBlock::move(const Vector2f& dir) {
		if (validMove(dir))
			rectangle.setPosition(rectangle.getPosition() + dir);
		collider.pos = rectangle.getPosition();
		update();
	}


	bool PlayerBlock::validMove(const Vector2f& dir) {
		Vector2f new_pos = rectangle.getPosition() + dir;
		return new_pos.x >= min_x && new_pos.x <= max_x;
	}


	Vector2f PlayerBlock::rebound(const sf::Vector2f& dir) {
		Vector2f normal(0, 1);
		Vector2f reflect = dir - (normal + normal);
		return reflect;
	}


	std::size_t PlayerBlock::getPointCount() const {
		return 4;
	}


	sf::Vector2f PlayerBlock::getPoint(std::size_t index) const {
		Vector2f point;

		switch (index)
		{
		case 0:
			point.x = rectangle.getPosition().x - rectangle.getSize().x / 2;
			point.y = rectangle.getPosition().y + rectangle.getSize().y / 2;
			break;
		case 1:
			point.x = rectangle.getPosition().x + rectangle.getSize().x / 2;
			point.y = rectangle.getPosition().y + rectangle.getSize().y / 2;
			break;
		case 2:
			point.x = rectangle.getPosition().x + rectangle.getSize().x / 2;
			point.y = rectangle.getPosition().y - rectangle.getSize().y / 2;
			break;
		case 3:
			point.x = rectangle.getPosition().x - rectangle.getSize().x / 2;
			point.y = rectangle.getPosition().y - rectangle.getSize().y / 2;
			break;
		}

		return point;
	}

	PHYSIC::Collider PlayerBlock::getCollider() {
		return collider;
	}
}