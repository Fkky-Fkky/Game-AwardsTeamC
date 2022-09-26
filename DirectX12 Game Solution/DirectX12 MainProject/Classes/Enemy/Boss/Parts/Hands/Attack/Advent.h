/**
* @file Advent.h
* @brief ƒ{ƒX‚Ìè~—Õˆ—ƒNƒ‰ƒX
*/

#pragma once

/**
* ƒCƒ“ƒNƒ‹[ƒhƒtƒ@ƒCƒ‹
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief AdventƒNƒ‰ƒX’è‹`
	*/
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

		int advent_state_; /**< ~—Õs“®Ši”[ */
		float time_delta_; /**< ŠÔŠi”[ */

		SimpleMath::Vector3 l_pos_; /**< ¶è‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 r_pos_; /**< ‰Eè‚ÌÀ•WŠi”[ */
		SimpleMath::Vector3 l_rot_; /**< ¶è‚Ì‰ñ“]Ši”[ */
		SimpleMath::Vector3 r_rot_; /**< ‰Eè‚Ì‰ñ“]Ši”[ */

		/**< ~—Õs“®‚Ìí—Ş */
		enum ADVENT_STATE_ {
			ADVENT_ACTION, /**< ~—Õ */
			ACTION_END /**< s“®I—¹ */
		};
	};
}