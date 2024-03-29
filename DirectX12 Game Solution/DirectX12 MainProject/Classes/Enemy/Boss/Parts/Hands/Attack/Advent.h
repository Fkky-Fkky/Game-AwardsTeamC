/**
* @file Advent.h
* @brief {XÌè~ÕNX
* @author ã½
*/

#pragma once

/**
* CN[ht@C
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief AdventNXè`
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

		int advent_state_; /**< ~Õs®i[ */
		float time_delta_; /**< Ôi[ */

		SimpleMath::Vector3 l_pos_; /**< ¶èÌÀWi[ */
		SimpleMath::Vector3 r_pos_; /**< EèÌÀWi[ */
		SimpleMath::Vector3 l_rot_; /**< ¶èÌñ]i[ */
		SimpleMath::Vector3 r_rot_; /**< EèÌñ]i[ */

		/**< ~Õs®ÌíÞ */
		enum ADVENT_STATE_ {
			ADVENT_ACTION, /**< ~Õ */
			ACTION_END /**< s®I¹ */
		};
	};
}