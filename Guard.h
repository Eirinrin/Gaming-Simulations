#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Guard : public SimObject	{
	public:
		Guard();
		~Guard();
		float flipTime;
		bool UpdateObject(float dt) override;

	protected:
	};
}