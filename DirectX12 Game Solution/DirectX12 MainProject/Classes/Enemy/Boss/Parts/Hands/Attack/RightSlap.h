#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	class RightSlap : public BossAction {
	public:
		RightSlap() {
			action_state_ = HAND_CHECK;
			time_delta_ = 0.0f;
			wait_time_  = 0.0f;
			hand_state_ = false;
			pos_ = SimpleMath::Vector3::Zero;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(ActionManager* const act_m);
		void Wait(ActionManager* const act_m);
		void RightSlapAttack(ActionManager* const act_m);
		void Reset();
		void HandReturn();

		int action_state_;

		float time_delta_;
		float wait_time_;

		bool hand_state_;

		SimpleMath::Vector3 pos_;
	};
}