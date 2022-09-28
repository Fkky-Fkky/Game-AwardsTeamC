/**
* @file PlayerRightMove.h
* @brief プレイヤー右移動処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerRightMoveクラス定義
	*/
	class PlayerRightMove : public PlayerActionState {
	public:
		PlayerRightMove() {};
		~PlayerRightMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}