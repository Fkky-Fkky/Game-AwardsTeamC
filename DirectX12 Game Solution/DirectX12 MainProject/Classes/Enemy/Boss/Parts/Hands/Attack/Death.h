#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

namespace boss {
	class Death : public BossAttack {
	public:
		Death() {
			time_delta_ = 0.0f;
			l_pos_ = SimpleMath::Vector3::Zero;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_rot_ = SimpleMath::Vector3::Zero;
			r_rot_ = SimpleMath::Vector3::Zero;
		};
		~Death() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

	private:

		float time_delta_;
		SimpleMath::Vector3 l_pos_;
		SimpleMath::Vector3 r_pos_;
		SimpleMath::Vector3 l_rot_;
		SimpleMath::Vector3 r_rot_;
	};
}