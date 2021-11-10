#include "Block.h"
#include <SFML/Graphics.hpp>
#include "Physic.h"
#include <iostream>

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
		/*rectangle.setSize(size);
		rectangle.setPosition(pos);
		rectangle.setFillColor(Color(255, 0, 0));*/
		m_pos = pos;
		m_size = size;

		min_x = minX + size.x / 2;
		max_x = maxX - size.x / 2;

		collider.rect.left = pos.x - size.x / 2;
		collider.rect.top = pos.y - size.y / 2;
		collider.rect.width = size.x;
		collider.rect.height = size.y;

		update();
	}


	void PlayerBlock::move(const Vector2f& dir) {
		if (validMove(dir))
			m_pos += dir;
		collider.rect.left = m_pos.x - m_size.x / 2;
		collider.rect.top = m_pos.y - m_size.y / 2;
		update();
	}


	bool PlayerBlock::validMove(const Vector2f& dir) {
		Vector2f new_pos = m_pos + dir;
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
			point.x = m_pos.x - m_size.x / 2;
			point.y = m_pos.y + m_size.y / 2;
			break;
		case 1:
			point.x = m_pos.x + m_size.x / 2;
			point.y = m_pos.y + m_size.y / 2;
			break;
		case 2:
			point.x = m_pos.x + m_size.x / 2;
			point.y = m_pos.y - m_size.y / 2;
			break;
		case 3:
			point.x = m_pos.x - m_size.x / 2;
			point.y = m_pos.y - m_size.y / 2;
			break;
		}

		return point;
	}

	PHYSIC::Collider PlayerBlock::getCollider() {
		return collider;
	}


	


	DestoyingBlock::DestoyingBlock(Vector2f pos, Vector2f size, float hp) {
		m_pos = pos;
		m_size = size;
		m_hp = hp;

		m_collider.rect.left = pos.x - size.x / 2;
		m_collider.rect.top = pos.y - size.y / 2;
		m_collider.rect.width = size.x;
		m_collider.rect.height = size.y;

		update();
	}


	void DestoyingBlock::getDamage(float value) {
		m_hp -= value;
		std::cout << "get damage: " << value << std::endl;

		//if (m_hp <= 0)
			// TODO уничтожение объекта
	}


	std::size_t DestoyingBlock::getPointCount() const {
		return 4;
	}


	Vector2f DestoyingBlock::getPoint(std::size_t  index) const {
		Vector2f point;

		switch (index)
		{
		case 0:
			point.x = m_pos.x - m_size.x / 2;
			point.y = m_pos.y + m_size.y / 2;
			break;
		case 1:
			point.x = m_pos.x + m_size.x / 2;
			point.y = m_pos.y + m_size.y / 2;
			break;
		case 2:
			point.x = m_pos.x + m_size.x / 2;
			point.y = m_pos.y - m_size.y / 2;
			break;
		case 3:
			point.x = m_pos.x - m_size.x / 2;
			point.y = m_pos.y - m_size.y / 2;
			break;
		}

		return point;
	}

	PHYSIC::Collider DestoyingBlock::getCollider() {
		return m_collider;
	}
}