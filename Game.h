#pragma once
namespace GAME {
	class GameController {
	public:
		void getDamage() { m_HP--; };
		int getHPCount() { return m_HP; }
		void setHPCount(int value = 3) { m_HP = value; }

	private:
		int m_HP = 3;
	};
}