/**
* @file PlayerActionState.h
* @brief プレイヤー行動基底クラス
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
class PlayerActionManager;

namespace player {
	/**
	* @brief PlayerActionStateクラス定義
	*/
	class PlayerActionState {
	public:
		/**
		* @brief 値の初期化純粋仮想関数
		*/
		virtual void Initialize() = 0;

		/**
		* @brief 値の更新純粋仮想関数
		* 
		* @param[in] deltaTime 時間
		* @param[out] player プレイヤー
		* @param[out] act_m アクションマネージャー
		*/
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) = 0;

	protected:
		const float PLAYER_MOVE_SPEED_ = 10.0f; /**< 移動速度 */
		const float FALL_SPEED_ = 15.0f; /**< 落下速度 */
		const float PLAYER_ROTATION_ANGLE_ = 90.0f; /**< 向く角度 */
		const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f; /**< 最大移動可能X座標 */
		const float PLAYER_LIMIT_MIN_POS_X_ = -17.0f; /**< 最小移動可能X座標 */
	};
}