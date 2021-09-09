#pragma once
#include "SimObject.h"

namespace NCL::CSC3222 {
	class Froggo : public SimObject {
	public:
		Froggo();
		~Froggo();
		float flipTime;
		bool UpdateObject(float dt) override;

	protected:

	};
}