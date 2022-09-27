/**
* @file Death.h
* @brief ƒ{ƒX€–S‚Ìè‚Ìˆ—
* @author ãƒ•½
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief DeathƒNƒ‰ƒX’è‹`
	*/
	class Death : public BossAction {
	public:
		Death() {
			death_state_ = ATK_CANCEL;
			time_delta_ = 0.0f;
			death_jump_time_ = 0.0f;
			death_jump_y_ = 0.0f;
			l_pos_ = SimpleMath::Vector3::Zero;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_rot_ = SimpleMath::Vector3::Zero;
			r_rot_ = SimpleMath::Vector3::Zero;
		};
		~Death() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void AtkCancel(ActionManager* const act_m);
		void DeathAction(ActionManager* const act_m);

		int death_state_; /**< Œ»İ‚Ìs“®Ši”[ */
		float time_delta_; /**< ŠÔ*/
		float death_jump_time_; /**< è‚ª”ò‚ÔŠÔ */
		float death_jump_y_; /**< è‚ª”ò‚Ôˆ—Ši”[ */

		SimpleMath::Vector3 l_pos_; /**< ¶è‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 r_pos_; /**< ‰Eè‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 l_rot_; /**< ¶è‚Ì‰ñ“]Ši”[ */
		SimpleMath::Vector3 r_rot_; /**< ‰Eè‚Ì‰ñ“]Ši”[ */

		const float DEATH_JUMP_SPEED_Y_ = 2.0f; /**< è‚ª”ò‚ÔƒXƒs[ƒh */
		const float DEATH_JUMP_GRAVITY_ = 6.0f; /**< è‚ª”ò‚Ô‚Æ‚«‚Ìd—Í */
		const float DEATH_ROT_X_ = 150.0f; /**< €–S‚Ì‰ñ“]X² */
		const float DEATH_POS_X_ = 18.0f; /**< €–S‚ÌXÀ•W */
		const float DEATH_POS_Y_ = 2.5f; /**< €–S‚ÌYÀ•W */

		/**< €–S‚Ìs“®í—Ş */
		enum DEATH_STATE_ {
			ATK_CANCEL, /**< UŒ‚‚ğI—¹ */
			DEATH_ACTION, /**< €–S‚Ìs“® */
			ACTION_END /**< s“®I—¹ */
		};
	};
}