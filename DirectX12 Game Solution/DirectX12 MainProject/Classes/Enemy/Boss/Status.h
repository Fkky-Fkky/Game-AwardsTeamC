/**
* @file Boss.h
* @brief ボスのステータスを処理するクラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace boss {
	/**
	* @brief Statusクラス定義
	*/
	class Status {
	public:
		Status() {
			damage_type_ = HAND;
			weak_count_ = 0;
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			weak_time_ = 0.0f;
			is_set_weak_time_ = false;
		};

		void Initialize();
		void Update(const float deltaTime, const ObjectManager* const obj_m);

		/**
		* @brief ボスのHP取得
		* 
		* @return ボスのHP
		*/
		float GetBossHP() const { return hp_; }

		/**
		* @brief ウィーク状態取得
		* 
		* @retval TRUE ウィーク状態
		* @retval FALSE ウィーク状態ではない
		*/
		bool IsWeak() const { return weak_count_ >= WEAK_COUNT_MAX_; }
	private:
		void DamageProcess();

		int damage_type_; /**< ダメージの種類を格納 */
		int weak_count_; /**< 攻撃された回数 */
		float hp_; /**< ボスのHP */
		float invincible_time_; /**< 無敵時間 */
		float weak_time_; /**< ウィーク状態の時間 */
		bool is_set_weak_time_; /**< ウィーク状態の時間を設定したか */
		const int WEAK_COUNT_MAX_ = 3; /**< ウィーク状態になるまでの回数 */
		const float BOSS_HP_MAX_ = 30.0f; /**< ボスの最大HP */
		const float HAND_DAMAGE_ = 1.0f; /**< 手が攻撃を受けた時のダメージ量 */
		const float BODY_DAMAGE_ = 5.0f; /**< 本体が攻撃を受けた時のダメージ量 */
		const float INVINCIBLE_TIME_MAX_ = 2.0f; /**< 無敵時間の最大値 */
		const float WEAK_TIME_MAX_ = 5.0f; /**< ウィーク時間の最大値 */

		/**
		* 受けるダメージのタイプ 
		*/
		enum DAMAGE_TYPE_ {
			HAND, /**< 手 */
			BODY /**< 本体 */
		};
	};
}