/**
* @file BeatRush.h
* @brief 連続叩きつけ攻撃処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief BeatRushクラス定義
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

		int action_state_; /**< 現在の攻撃行動格納 */

		float r_beat_time_; /**< 右手の攻撃時間格納 */
		float l_beat_time_; /**< 左手の攻撃時間格納 */
		float r_move_dest_x_; /**< 右手の移動先格納 */
		float l_move_dest_x_; /**< 左手の移動先格納 */
		float time_delta_; /**< 時間 */
		float wait_time_; /**< 待機時間 */

		bool r_hand_up_flag_; /**< 右手を上にあげるか */
		bool l_hand_up_flag_; /**< 左手を上にあげるか */
		bool is_r_attack_end_; /**< 右手の攻撃が終了したか */
		bool is_l_attack_end_; /**< 左手の攻撃が終了したか */
		bool is_r_return_end_; /**< 右手が初期座標に移動したか */
		bool is_l_return_end_; /**< 左手が初期座標に移動したか */

		SimpleMath::Vector3 r_pos_; /**< 右手の座標格納 */
		SimpleMath::Vector3 r_rote_; /**< 右手の回転格納 */
		SimpleMath::Vector3 l_pos_; /**< 左手の座標格納 */
		SimpleMath::Vector3 l_rote_; /**< 左手の回転格納 */

		const float R_START_POS_X_ = -15.0f; /**< 右手の構える位置 */
		const float L_START_POS_X_ = -10.0f; /**< 左手の構える位置 */

		const float WAIT_TIME_MAX_ = 0.5f; /**< 待機時間 */
		const float BEAT_L_START_TIME_ = 0.5f; /**< 左手が攻撃を始める時間 */
		const float ADD_DISTANCE_ = 13.0f; /**< 移動先に追加するX座標 */
	};
}