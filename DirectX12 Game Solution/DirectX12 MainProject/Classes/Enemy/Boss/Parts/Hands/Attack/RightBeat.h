/**
* @file LeftBeat.h
* @brief ¶’@‚«‚Â‚¯UŒ‚ˆ—ƒNƒ‰ƒX
* @author ãƒ•½
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief RightBeatƒNƒ‰ƒX’è‹`
	*/
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

		int boss_action_state_; /**< Œ»İ‚ÌUŒ‚s“®Ši”[ */

		float time_delta_; /**< ŠÔŠi”[ */
		float beat_time_; /**< ’@‚«‚Â‚¯UŒ‚‚ÌŠÔŠi”[ */
		float wait_time_; /**< ‘Ò‹@ŠÔŠi”[ */
		float ready_time_; /**< \‚¦‚ÌŠÔŠi”[ */
		float limit_pos_y_; /**< YÀ•W‚Ì”ÍˆÍŠi”[ */

		bool hand_state_; /**< è‚Ìó‘ÔŠi”[ */
		bool is_player_pos_arrival_; /**< è‚ªƒvƒŒƒCƒ„[‚ÌÀ•W‚É“’…‚µ‚½‚© */

		SimpleMath::Vector3 pos_; /**< è‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 rote_; /**< è‚Ì‰ñ“]Ši”[ */

		const float CHASE_SPEED_ = 6.0f; /**< ƒvƒŒƒCƒ„[‚ğ’Ç‚¢‚©‚¯‚éƒXƒs[ƒh */
		const float CHASE_PLAYER_TIME_ = 2.0f; /**< ƒvƒŒƒCƒ„[‚ğ’Ç‚¢‚©‚¯‚éŠÔ */
		const float READY_TIME_MAX_	   = 2.3f; /**< \‚¦‚ÌŠÔ */
		const float WAIT_TIME_MAX_	   = 1.5f; /**< ‘Ò‹@ŠÔ */
	};
}