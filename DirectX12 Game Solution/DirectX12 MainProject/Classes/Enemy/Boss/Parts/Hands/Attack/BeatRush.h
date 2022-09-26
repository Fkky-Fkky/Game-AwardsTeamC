/**
* @file BeatRush.h
* @brief ˜A‘±’@‚«‚Â‚¯UŒ‚ˆ—ƒNƒ‰ƒX
* @outhor ãƒ•½
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief BeatRushƒNƒ‰ƒX’è‹`
	*/
	class BeatRush : public BossAction {
	public:
		BeatRush() {
			action_state_ = HAND_CHECK;
			r_beat_time_ = 0.0f;
			l_beat_time_ = 0.0f;
			l_move_dest_x_ = 0.0f;
			time_delta_ = 0.0f;
			wait_time_ = 0.0f;
			r_move_dest_x_ = 0.0f;
			r_hand_up_flag_ = false;
			l_hand_up_flag_ = false;
			is_r_attack_end_ = false;
			is_l_attack_end_ = false;
			is_r_return_end_ = false;
			is_l_return_end_ = false;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck();
		void Ready();
		void Attack(ActionManager* const act_m);
		void BeatR(ActionManager* const act_m);
		void BeatL(ActionManager* const act_m);
		void Reset();
		void HandReturn();

		int action_state_; /**< Œ»İ‚ÌUŒ‚s“®Ši”[ */

		float r_beat_time_; /**< ‰Eè‚ÌUŒ‚ŠÔŠi”[ */
		float l_beat_time_; /**< ¶è‚ÌUŒ‚ŠÔŠi”[ */
		float r_move_dest_x_; /**< ‰Eè‚ÌˆÚ“®æŠi”[ */
		float l_move_dest_x_; /**< ¶è‚ÌˆÚ“®æŠi”[ */
		float time_delta_; /**< ŠÔ */
		float wait_time_; /**< ‘Ò‹@ŠÔ */

		bool r_hand_up_flag_; /**< ‰Eè‚ğã‚É‚ ‚°‚é‚© */
		bool l_hand_up_flag_; /**< ¶è‚ğã‚É‚ ‚°‚é‚© */
		bool is_r_attack_end_; /**< ‰Eè‚ÌUŒ‚‚ªI—¹‚µ‚½‚© */
		bool is_l_attack_end_; /**< ¶è‚ÌUŒ‚‚ªI—¹‚µ‚½‚© */
		bool is_r_return_end_; /**< ‰Eè‚ª‰ŠúÀ•W‚ÉˆÚ“®‚µ‚½‚© */
		bool is_l_return_end_; /**< ¶è‚ª‰ŠúÀ•W‚ÉˆÚ“®‚µ‚½‚© */

		SimpleMath::Vector3 r_pos_; /**< ‰Eè‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 r_rote_; /**< ‰Eè‚Ì‰ñ“]Ši”[ */
		SimpleMath::Vector3 l_pos_; /**< ¶è‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 l_rote_; /**< ¶è‚Ì‰ñ“]Ši”[ */

		const float R_START_POS_X_ = -15.0f; /**< ‰Eè‚Ì\‚¦‚éˆÊ’u */
		const float L_START_POS_X_ = -10.0f; /**< ¶è‚Ì\‚¦‚éˆÊ’u */

		const float WAIT_TIME_MAX_ = 0.5f; /**< ‘Ò‹@ŠÔ */
		const float BEAT_L_START_TIME_ = 0.5f; /**< ¶è‚ªUŒ‚‚ğn‚ß‚éŠÔ */
		const float ADD_DISTANCE_ = 13.0f; /**< ˆÚ“®æ‚É’Ç‰Á‚·‚éXÀ•W */
	};
}