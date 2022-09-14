#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

namespace boss {
	class Death : public BossAttack {
	public:
		Death() {
			death_state_ = ATK_CANCEL;
			time_delta_ = 0.0f;
			l_pos_ = SimpleMath::Vector3::Zero;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_rot_ = SimpleMath::Vector3::Zero;
			r_rot_ = SimpleMath::Vector3::Zero;
		};
		~Death() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

	private:
		void AtkCancel(HandManager* const hand_m);
		void DeathAction();

		int death_state_;
		float time_delta_;
		float death_time_y_;
		float death_y_;

		SimpleMath::Vector3 l_pos_;
		SimpleMath::Vector3 r_pos_;
		SimpleMath::Vector3 l_rot_;
		SimpleMath::Vector3 r_rot_;

		const float DEATH_ROT_X_ = 150.0f;
		const float DEATH_POS_X_ = 18.0f;
		const float DEATH_POS_Y_ = 3.0f;

		enum DEATH_STATE_ {
			ATK_CANCEL,
			DEATH_ACTION,
			ACTION_END
		};
	};
}