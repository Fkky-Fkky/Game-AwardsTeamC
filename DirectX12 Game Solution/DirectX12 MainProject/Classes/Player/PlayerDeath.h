/**
* @file PlayerDeath.h
* @brief プレイヤー死亡処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerDeathクラス定義
	*/
	class PlayerDeath : public PlayerActionState {
	public:
		PlayerDeath() {
			is_player_death_ = false;
		};
		~PlayerDeath() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);
		
		/**
		* @brief プレイヤーが死亡しているか
		* 
		* @retval TRUE 死亡している
		* @retval FALSE 死亡していない
		*/
		bool IsPlayerDeath()const { return is_player_death_; }

	private:
		bool is_player_death_; /**< プレイヤーが死亡している*/

		const float DEATH_POS_Y_ = 0.1f; /**< 死亡時のY座標 */
	};
}