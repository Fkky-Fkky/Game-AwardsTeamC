/**
* @file BossAction.h
* @brief ボスの行動基底クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include "Base/DX12Effekseer.h"

/**
* クラス参照
*/
class ObjectManager;
class ActionManager;

using namespace DirectX;

namespace boss {
	/**
	* @brief BossAction定義
	*/
	class BossAction {
	public:
		BossAction() {
			slap_speed_  = 0.0f;
			slap_y_time_ = 0.0f;
			is_se_play_	  = false;
			is_shake_set_ = false;
			boss_handL_ = nullptr;
			boss_handR_ = nullptr;
		}

		virtual void Initialize(BossHand* const boss_handL, BossHand* const boss_handR);
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) = 0;

	private:
		float slap_y_time_; /**< 薙ぎ払い構え時の時間 */
		bool is_se_play_; /**< SEを再生したか */
		bool is_shake_set_; /**< カメラ横揺れ設定したか */
		const float SLAP_SPEED_Y_	= 2.0f; /**< 薙ぎ払い構えの速度 */
		const float SLAP_GRAVITY_Y_ = 5.0f; /**< 薙ぎ払い構えの重力 */

	protected:
		virtual void SlapAttackBase(const float deltaTime, ActionManager* const act_m);
		virtual float SlapY(const float deltaTime);

		BossHand* boss_handL_; /**< ボス左手格納 */
		BossHand* boss_handR_; /**< ボス右手格納 */
		float slap_speed_; /**< 薙ぎ払い攻撃のスピード格納 */


		const float HAND_R_INITIAL_POS_X_ = -13.0f; /**< 右手の初期X座標 */
		const float HAND_L_INITIAL_POS_X_ = 13.0f; /**< 左手の初期X座標 */
		const float HAND_INITIAL_POS_Y_ = 13.0f; /**< 手の初期Y座標 */
		const float HAND_INITIAL_POS_Z_ = 10.0f; /**< 手の初期Z座標 */

		const float HAND_INITIAL_ROT_X_ = 30.0f; /**< 手の初期回転X軸 */

		const float ATTACK_POS_Z_ = -2.0f; /**< 攻撃時のZ座標 */
		const float HAND_LIMIT_POS_X_ = 70.0f; /**< 手の最大移動X範囲*/
		const float HAND_ROCK_LIMIT_POS_Y_ = 3.0f; /**< 手握り状態時の最大移動Y範囲 */
		const float HAND_RETURN_POS_X_ = 30.0f; /**< 手が初期位置に戻る時のスタートX座標 */

		const float SLAP_POS_Y_ = 0.5f; /**< 薙ぎ払い攻撃時のY座標 */
		const float SLAP_SPEED_MAX_X_ = 40.0f; /**< 薙ぎ払い攻撃時の最大速度 */
		const float ADD_SLAP_SPEED_ = 20.0f; /**< 薙ぎ払い攻撃の加速度 */

		const float WAIT_TIME_MAX_ = 0.7f; /**< 待機時間 */

		const float BEAT_SPEED_ = 3.5f; /**< 叩きつけ攻撃のスピード */
		const float BEAT_GRAVITY_ = 15.0f; /**< 叩きつけ攻撃の重力 */
		const float BEAT_HAND_ROCK_ROT_X_ = 90.0f; /**< 手握り状態時の回転X軸 */

		const float MOVE_SPEED_X_ = 20.0f; /**< X座標移動速度 */
		const float MOVE_SPEED_Y_ = 10.0f; /**< Y座標移動速度 */
		const float MOVE_SPEED_Z_ = 20.0f; /**< Z座標移動速度 */
		const float ROTE_SPEED_ = 200.0f; /**< 回転速度 */

		const float HALF_ = 0.5f; /**< 半分 */

		/**< 行動の種類 */
		enum ACTION_STATE {
			HAND_CHECK, /**< 手の状態確認 */
			READY, /**< 構え */
			WAIT, /**< 待機 */
			ATTACK, /**< 攻撃 */
			RESET, /**< 値のリセット */
			RETURN, /**< 手を初期位置に戻す */
			ACTION_END /**< 行動終了 */
		};

		/**< 手のモーション */
		enum HAND_MOTION {
			WAIT_MOTION, /**< 待機 */
			PAPER, /**< 手を開く */
			PAPER_BACK, /**< 開いた状態から待機へ戻す */
			ROCK, /**< 手を握る */
			ROCK_BACK /**< 握った状態から待機へ戻す */
		};
	};
}