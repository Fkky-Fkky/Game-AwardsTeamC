/**
* @file PlayerLeftMove.h
* @brief プレイヤー左移動処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerLeftMoveクラス定義
	*/
	class PlayerLeftMove : public PlayerActionState {
	public:
		PlayerLeftMove() {};
		~PlayerLeftMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}