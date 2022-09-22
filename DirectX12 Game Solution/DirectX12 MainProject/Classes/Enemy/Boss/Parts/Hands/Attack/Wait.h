#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	class Wait : public BossAction {
	public:
		Wait() {
			wait_time_ = 0.0f;
			max_wait_time_ = 0.0f;
			first_processed_flag_ = false;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		float wait_time_;
		float max_wait_time_;
		bool first_processed_flag_;
		const float HP_NORMAL_MAX_ = 30.0f;
		const float HP_NORMAL_MIN_ = 20.0f;
		const float HP_HARD_MIN_ = 10.0f;
		const float MAX_WAIT_TIME_NORMAL_ = 1.0f;
		const float MAX_WAIT_TIME_HARD_ = 0.7f;
		const float MAX_WAIT_TIME_VERY_HARD_ = 0.5f;
	};
}