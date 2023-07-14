/**
* @file PlayerAttackCollision.h
* @brief プレイヤー攻撃コリジョン処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class Player;

namespace player {
	/**
	* @brief PayerAttackCollisionクラス定義
	*/
	class PlayerAttackCollision {
	public:
		PlayerAttackCollision() {
			attack_time_ = 0.0f;
			is_player_attack_ = false;
			is_effect_play_ = false;
			is_se_play_ = false;
		}
		~PlayerAttackCollision() {};

		void Initialize();
		void LoadAssets(DX9::SkinnedModel* const model_);
		void Update(const float deltaTime, const DX9::SkinnedModel* const model_, const Player* const player);

		/**
		* @brief プレイヤーは攻撃しているか
		* 
		* @retval TRUE している
		* @retval FALSE していない
		*/
		bool IsPlayerAttack() const { return is_player_attack_; }

		/**
		* @brief プレイヤーの攻撃コリジョン取得
		* 
		* @return 攻撃コリジョン
		*/
		BoundingOrientedBox GetAttackCollision() const { return collision_; }
	private:
		void AtkProcess(const Player* const player);
		BoundingOrientedBox collision_;
		float attack_time_; /**< 攻撃する時間格納 */
		bool is_player_attack_; /**< 攻撃をしているか */
		bool is_effect_play_; /**< エフェクトを再生したか */
		bool is_se_play_; /**< SEを再生したか */

		const float PLAYER_RIGHT_ = -90.0f; /**< プレイヤー右向き */
		const float RIGHT_ANGLE_ = 0.0f; /**< エフェクトの右向き */
		const float LEFT_ANGLE_ = 200.0f; /**< エフェクトの左向き */
		const float MAX_ATTACK_TIME_ = 3.3f; /**< 最大攻撃時間 */
		const float ATTACK_DISTANCE_X_ = 4.5f; /**< 攻撃コリジョンのX座標 */
		const float ATTACK_DISTANCE_Y_ = 1.5f; /**< 攻撃コリジョンのY座標 */
		const float ATTACK_START_TIME_ = 1.3f; /**< 攻撃を始める時間 */
		const float ATTACK_END_TIME_ = 1.7f; /**< 攻撃を終わらせる時間 */
		const float COLLISION_SIZE_MULTIPLY_X_ = 0.1f; /**< コリジョンのXサイズ */
		const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f; /**< コリジョンのYサイズ */
		const float COLLISION_SIZE_MULTIPLY_Z_ = 4.0f; /**< コリジョンのZサイズ */
	};
}