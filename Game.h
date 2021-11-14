#pragma once
#include "Reset.h"
#include <vector>

namespace GAME {
	class GameController {
	public:
		void getDamage() { m_HP--; };
		int getHPCount() { return m_HP; }
		void setHPCount(int value = 3) { m_HP = value; }
		void resetGame(std::vector<RESET::IResetableObject*> resetObj) {
			for (auto obj : resetObj) {
				obj->reset();
			}
			setHPCount();
		}

	private:
		int m_HP = 3;
	};
}