#pragma once
namespace RESET {
	class IResetableObject {
	public:
		virtual void reset() = 0;
	};
}