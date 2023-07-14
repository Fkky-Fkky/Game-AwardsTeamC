/**
* @file PlayerDamage.h
* @brief プレイヤーダメージ処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerDamageクラス定義
	*/
	class PlayerDamage : public PlayerActionState {
	public:
		PlayerDamage() {
			dmg_time = 0.0f;
			knock_back_dest_ = 0.0f;
			one_process_flag_ = false;
			is_invinsible_ = false;
		}
		~PlayerDamage() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

		/**
		* @brief プレイヤーが無敵か
		* 
		* @retval TRUE 無敵
		* @retval FALSE 無敵ではない
		*/
		bool IsInvincible() const { return is_invinsible_; }
	private:

		float dmg_time; /**< ダメージ状態の時間格納 */
		float knock_back_dest_; /**< ノックバックの移動先 */
		bool one_process_flag_; /**< 一度だけ処理する */
		bool is_invinsible_; /**< 無敵か */

		SimpleMath::Vector3 pos_; /**< 座標格納 */
		SimpleMath::Vector3 rot_; /**< 回転格納 */
		const float ADD_DEST_ = 3.0f; /**< 追加する移動先 */
		const float KNOCK_BACK_SPEED_ = 20.0f; /**< ノックバック速度 */
		const float DMG_TIME_MAX_ = 0.6f; /**< ダメージ状態の時間 */
	};
}