/**
* @file Death.h
* @brief ボス死亡時の手の処理
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Deathクラス定義
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

		int death_state_; /**< 現在の行動格納 */
		float time_delta_; /**< 時間*/
		float death_jump_time_; /**< 手が飛ぶ時間 */
		float death_jump_y_; /**< 手が飛ぶ処理格納 */

		SimpleMath::Vector3 l_pos_; /**< 左手の座標格納 */
		SimpleMath::Vector3 r_pos_; /**< 右手の座標格納 */
		SimpleMath::Vector3 l_rot_; /**< 左手の回転格納 */
		SimpleMath::Vector3 r_rot_; /**< 右手の回転格納 */

		const float DEATH_JUMP_SPEED_Y_ = 2.0f; /**< 手が飛ぶスピード */
		const float DEATH_JUMP_GRAVITY_ = 6.0f; /**< 手が飛ぶときの重力 */
		const float DEATH_ROT_X_ = 150.0f; /**< 死亡時の回転X軸 */
		const float DEATH_POS_X_ = 18.0f; /**< 死亡時のX座標 */
		const float DEATH_POS_Y_ = 2.5f; /**< 死亡時のY座標 */

		/**< 死亡時の行動種類 */
		enum DEATH_STATE_ {
			ATK_CANCEL, /**< 攻撃を終了 */
			DEATH_ACTION, /**< 死亡時の行動 */
			ACTION_END /**< 行動終了 */
		};
	};
}