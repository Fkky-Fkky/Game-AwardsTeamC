/**
* @file BossBody.h
* @brief ボスの本体を処理するクラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class ObjectManager;
class Boss;

namespace boss {
	/**
	* @brief BossBodyクラス定義
	*/
	class BossBody : public BossParts {
	public:
		BossBody() {
			time_delta_		= 0.0f;
			shake_time_		= 0.0f;
			body_jump_y_	= 0.0f;
			body_jump_time_ = 0.0f;
			is_weak_		= false;
			is_shake_		= false;
			shake_set_flag_ = false;
			is_body_death_  = false;
			is_shake_reset_ = false;
			is_start_pos_	= false;
		}
		~BossBody() {};

		virtual void Initialize();
		void LoadAssets();
		void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);

		/**
		* @brief ボス本体が死んでいるか
		* 
		* @retval TRUE 死んでいる
		* @retval FALSE 死んでいない
		*/
		bool IsBodyDeath() const { return is_body_death_; }

		/**
		* @brief ボス本体のコリジョン取得
		* 
		* @return ボス本体のコリジョン
		*/
		BoundingOrientedBox GetBodyCollision() const { return body_coll_; }
	private:
		void AdventAction();
		void WeakAction();
		void DeathAction();

		BoundingOrientedBox body_coll_; /**< コリジョンを格納 */
		float time_delta_; /**< 時間を格納 */
		float shake_time_; /**< 画面を揺らす時間格納 */
		float body_jump_y_; /**< 飛ぶ時の数値格納 */
		float body_jump_time_; /**< 飛ぶ時間 */
		bool is_weak_; /**< ウィーク状態か */
		bool is_shake_; /**< 画面が揺れているか */
		bool shake_set_flag_; /**< 画面揺れを設定したか */
		bool is_body_death_; /**< 本体が死んでいるか */
		bool is_shake_reset_; /**< 画面揺れをリセットしたか */
		bool is_start_pos_; /**< スタート位置にいるか */

		const float BODY_INIT_POS_Y_  = 50.0f; /**< 初期Y座標 */
		const float BODY_INIT_POS_Z_  = 15.0f; /**< 初期Z座標 */
		const float BODY_INIT_ROT_X_  = -20.0f; /**< 初期回転X軸 */
		const float BODY_START_POS_Y_ = 17.0f; /**< スタート位置 */
		const float BODY_WEAK_POS_Y_  = 5.0f; /**< ウィーク状態時のY座標 */
		const float BODY_WEAK_POS_Z_  = 5.0f; /**< ウィーク状態時のZ座標 */
		const float BODY_DEATH_POS_Y_ = 4.0f; /**< 死亡時のZ座標 */
		const float DEATH_ROTATION_X_ = 40.0f; /**< 死亡時の回転X軸 */
		const float BODY_SCALE_ = 0.8f; /**< モデルの大きさ */
		const float COLLISION_SIZE_X_ = 0.1f; /**< 当たり判定のXサイズ */
		const float COLLISION_SIZE_Z_ = 0.8f; /**< 当たり判定のZサイズ */
		const float ADVENT_SPEED_	 = 10.0f; /**< 登場時の降りてくるスピード */
		const float BODY_UP_SPEED_Y_ = 10.0f; /**< 上に移動するスピード */
		const float MOVE_SPEED_Z_	 = 20.0f; /**< Z座標で動くスピード */
		const float JUMP_SPEED_		 = 1.0f; /**< 飛ぶときの初速 */
		const float ROTATION_SPEED_  = 10.0f; /**< 回転するスピード */
		const float DEATH_ROTATION_SPEED_ = 80.0f; /**< 死亡時の回転するスピード */
		const float SHAKE_TIME_MAX_ = 0.2f; /**< 画面揺れする時間 */
		const float HALF_		= 0.5f; /**< 半分 */
		const float GRAVITY_	= 2.0f; /**< 重力 */
	};
}