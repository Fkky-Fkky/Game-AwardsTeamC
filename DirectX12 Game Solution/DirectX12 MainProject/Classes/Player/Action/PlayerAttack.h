/**
* @file PlayerAttack.h
* @brief プレイヤー攻撃処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerAttackクラス定義
	*/
	class PlayerAttack : public PlayerActionState {
	public:
		PlayerAttack() {
			attack_time_ = 0.0f;
			attack_flg_ = false;
		};
		~PlayerAttack() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

		/**
		* @brief プレイヤーが攻撃を始めたか
		* 
		* @retval TRUE 始めた
		* @ratval FALSE 始めていない
		*/
		bool IsPlayerAttackStart() const { return attack_flg_; }

	private:
		float attack_time_; /**< 攻撃時間格納 */
		bool attack_flg_; /**< 攻撃フラグ */
		const float MAX_ATTACK_TIME_ = 3.3f; /**< 最大攻撃時間 */
	};
}