/**
* @file DoubleSlap.h
* @brief 両手薙ぎ払い攻撃処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief DoubleSlapクラス定義
	*/
	class DoubleSlap : public BossAction {
	public:
		DoubleSlap() {
			action_state_ = HAND_CHECK;
			time_delta_ = 0.0f;
			slap_y_		= 0.0f;
			l_slap_speed_x_ = 0.0f;
			wait_time_		= 0.0f;
			ready_end_r_ = false;
			ready_end_l_ = false;
			atk_end_r_ = false;
			atk_end_l_ = false;
			return_end_r_ = false;
			return_end_l_ = false;
			hand_state_ = false;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_pos_ = SimpleMath::Vector3::Zero;
		}

		~DoubleSlap() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(ActionManager* const act_m);
		void ReadyR();
		void ReadyL();
		void Attack(ActionManager* const act_m);
		void SlapR(ActionManager* const act_m);
		void SlapL();
		void Reset();
		void HandReturn();

		int action_state_; /**< 現在の攻撃行動格納 */

		float time_delta_; /**< 時間 */
		float slap_y_; /**< 構えに必要な処理格納 */
		float l_slap_speed_x_; /**< 左薙ぎ払いスピード格納 */
		float wait_time_; /**< 待機時間格納 */

		bool ready_end_r_; /**< 右手構えが完了したか */
		bool ready_end_l_; /**< 左手構えが完了したか */
		bool atk_end_r_; /**< 右手の攻撃が完了したか */
		bool atk_end_l_; /**< 左手の攻撃が完了したか */
		bool return_end_r_; /**< 右手が初期座標に移動したか */
		bool return_end_l_; /**< 左手が初期座標に移動したか */
		bool hand_state_; /**< 手の状態格納 */

		SimpleMath::Vector3 r_pos_; /**< 右手の座標格納 */
		SimpleMath::Vector3 l_pos_; /**< 左手の座標格納 */

		const float L_HAND_DEST_Y_ = 8.0f; /**< 左手の移動先Y座標 */
		const float ATTACK_START_TIME_R_ = 1.0f; /**< 右手の攻撃開始時間 */
		const float WAIT_TIME_MAX_ = 1.5f; /**< 最大待機時間 */
	};
}