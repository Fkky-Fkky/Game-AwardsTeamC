/**
* @file LeftBeat.h
* @brief 左叩きつけ攻撃処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief LeftBeatクラス定義
	*/
	class LeftBeat : public BossAction {
	public:
		LeftBeat() {
			boss_action_state_ = HAND_CHECK;
			time_delta_  = 0.0f;
			beat_time_   = 0.0f;
			wait_time_	 = 0.0f;
			ready_time_	 = 0.0f;
			limit_pos_y_ = 0.0f;
			hand_state_	 = false;
			is_player_pos_arrival_ = false;
			pos_  = SimpleMath::Vector3::Zero;
			rote_ = SimpleMath::Vector3::Zero;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(const ObjectManager* const obj_m);
		void LeftBeatAttack(ActionManager* const act_m);
		void Wait(ActionManager* const act_m);
		void HandReturn();

		int boss_action_state_; /**< 現在の攻撃行動格納 */

		float time_delta_; /**< 時間格納 */
		float beat_time_; /**< 叩きつけ攻撃の時間格納 */
		float wait_time_; /**< 待機時間格納 */
		float ready_time_; /**< 構えの時間格納 */
		float limit_pos_y_; /**< Y座標の範囲格納 */

		bool hand_state_; /**< 手の状態格納 */
		bool is_player_pos_arrival_; /**< 手がプレイヤーの座標に到着したか */

		SimpleMath::Vector3 pos_; /**< 手の座標格納 */
		SimpleMath::Vector3 rote_; /**< 手の回転格納 */

		const float CHASE_SPEED_ = 6.0f; /**< プレイヤーを追いかけるスピード */
		const float CHASE_PLAYER_TIME_ = 2.0f; /**< プレイヤーを追いかける時間 */
		const float READY_TIME_MAX_	   = 2.3f; /**< 構えの時間 */
		const float WAIT_TIME_MAX_	   = 1.5f; /**< 待機時間 */
	};
}