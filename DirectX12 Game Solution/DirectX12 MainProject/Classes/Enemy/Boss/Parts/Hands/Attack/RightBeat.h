#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	class RightBeat : public BossAction {
	public:
		RightBeat() {
			boss_action_state_ = HAND_CHECK;
			time_delta_  = 0.0f;
			beat_time_   = 0.0f;
			wait_time_   = 0.0f;
			ready_time_	 = 0.0f;
			limit_pos_y_ = 0.0f;
			hand_state_  = false;
			is_player_pos_arrival_ = false;
			pos_  = SimpleMath::Vector3::Zero;
			rote_ = SimpleMath::Vector3::Zero;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(const ObjectManager* const obj_m);
		void RightBeatAttack(ActionManager* const act_m);
		void Wait(ActionManager* const act_m);
		void HandReturn();

		int boss_action_state_;

		float time_delta_;
		float beat_time_;
		float wait_time_;
		float ready_time_;
		float limit_pos_y_;

		bool hand_state_;
		bool is_player_pos_arrival_;

		SimpleMath::Vector3 pos_;
		SimpleMath::Vector3 rote_;

		const float CHASE_SPEED_ = 6.0f;
		const float CHASE_PLAYER_TIME_ = 2.0f;
		const float READY_TIME_MAX_	   = 2.3f;
		const float WAIT_TIME_MAX_	   = 1.5f;
	};
}