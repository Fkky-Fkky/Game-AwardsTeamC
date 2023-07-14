/**
* @file LeftSlap.h
* @brief ¶“ã‚¬•¥‚¢UŒ‚ˆ—ƒNƒ‰ƒX
* @author ãƒ•½
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief RightSlapƒNƒ‰ƒX’è‹`
	*/
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

		int action_state_; /**< Œ»İ‚ÌUŒ‚s“®Ši”[ */

		float time_delta_; /**< ŠÔŠi”[ */
		float wait_time_; /**< ‘Ò‹@ŠÔŠi”[ */

		bool hand_state_; /**< è‚Ìó‘ÔŠi”[ */

		SimpleMath::Vector3 pos_; /**< è‚ÌÀ•WŠi”[ */
	};
}