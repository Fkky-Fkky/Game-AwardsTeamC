/**
* @file Weak.h
* @brief ウィーク処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Weakクラス定義
	*/
	class Weak : public BossAction {
	public:
		Weak() {
			weak_state_ = ATK_CANCEL;
			time_delta_ = 0.0f;
			weak_time_y_ = 0.0f;
			weak_y_ = 0.0f;
			pos_r_ = SimpleMath::Vector3::Zero;
			pos_l_ = SimpleMath::Vector3::Zero;
			rot_r_ = SimpleMath::Vector3::Zero;
			rot_l_ = SimpleMath::Vector3::Zero;
		}
		~Weak() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void AtkCancel(ActionManager* const act_m);
		void WeakAction(ActionManager* const act_m);
		void WeakR();
		void WeakL();
		void Wait(const ObjectManager* const obj_m, ActionManager* const act_m);
		void InitialPosMove();

		int weak_state_; /**< 現在の行動格納 */

		float time_delta_; /**< 時間格納 */
		float weak_time_y_; /**< 手が飛ぶ時の時間格納 */
		float weak_y_; /**< 手が飛ぶ処理格納 */

		SimpleMath::Vector3 pos_r_; /**< 右手の座標格納 */
		SimpleMath::Vector3 pos_l_; /**< 左手の座標格納 */
		SimpleMath::Vector3 rot_r_; /**< 右手の回転格納 */
		SimpleMath::Vector3 rot_l_; /**< 左手の回転格納 */

		const float WEAK_ROT_X_ = 150.0f; /**< ウィーク状態時の回転X軸 */
		const float WEAK_POS_X_ = 18.0f; /**< ウィーク状態時のX座標 */
		const float WEAK_POS_Y_ = 3.0f; /**< ウィーク状態時のY座標 */
		const float WEAK_SPEED_Y_ = 2.0f; /**< 手が飛ぶ時の時間 */
		const float WEAK_GRAVITY_ = 6.0f; /**< 手が飛ぶ時の重力 */

		/**< ウィーク状態行動種類 */
		enum WEAK_STATE {
			ATK_CANCEL, /**< 攻撃のキャンセル */
			WEAK_ACTION, /**< ウィーク */
			WAIT, /**< 待機 */
			INITIAL_POS_MOVE, /**< 初期座標へ移動 */
			ACTION_END /**< 行動終了 */
		};
	};
}