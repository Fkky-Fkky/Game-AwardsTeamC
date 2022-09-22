#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	class Advent : public BossAction {
	public:
		Advent() {
			advent_state_ = ADVENT_ACTION;
			time_delta_ = 0.0f;
			l_pos_ = SimpleMath::Vector3::Zero;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_rot_ = SimpleMath::Vector3::Zero;
			r_rot_ = SimpleMath::Vector3::Zero;
		};
		~Advent() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void AdventAction();

		int advent_state_;
		float time_delta_;

		SimpleMath::Vector3 l_pos_;
		SimpleMath::Vector3 r_pos_;
		SimpleMath::Vector3 l_rot_;
		SimpleMath::Vector3 r_rot_;

		enum ADVENT_STATE_ {
			ADVENT_ACTION,
			ACTION_END
		};
	};
}