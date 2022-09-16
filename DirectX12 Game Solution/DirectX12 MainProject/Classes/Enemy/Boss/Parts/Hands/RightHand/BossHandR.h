#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

namespace boss {
	class BossHandR : public BossHand {
	public:
		void Initialize();
		void LoadAssets();
		virtual void Update(const float deltaTime);

	private:
		const float INITIAL_POS_X_ = -13.0f;
		const float ADD_COLLISION_POS_X_ = -1.0f;
	};
}