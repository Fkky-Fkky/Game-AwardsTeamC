/**
* @file PlayerStatus.h
* @brief プレイヤーのHP処理クラス
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace player {
	/**
	* @brief PlayerStateクラス定義
	*/
	class PlayerStatus {
	public:
		PlayerStatus() {
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			damage_ = 0.0f;
			is_invincible_ = false;
		};
		~PlayerStatus() {};

		void Initialize();
		void Update(const float deltatime, const ObjectManager* const obj_m);

		/**
		* @brief プレイヤーのHP取得
		* 
		* @return HP
		*/
		float GetPlayerHP() const { return hp_; }
	private:
		void DamageProcess();
		
		float hp_; /**< HP格納 */
		float invincible_time_; /**< 無敵時間格納 */
		float damage_; /**< ダメージ量格納 */
		bool is_invincible_; /**< 無敵か */

		const float PLAYER_HP_MAX_ = 30.0f; /**< HP最大値 */
		const float INVINCIBLE_TIME_MAX_ = 1.5f; /**< 無敵時間 */
		const float OPEN_DAMAGE_ = 2.0f; /**< ボスの手が開いている場合のダメージ量 */
		const float CLOSE_DAMAGE_ = 4.0f; /**< ボスの手が握っている場合のダメージ量 */
	};
}