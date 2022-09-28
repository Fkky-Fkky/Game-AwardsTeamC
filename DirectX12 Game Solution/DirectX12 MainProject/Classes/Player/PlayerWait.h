/**
* @file PlayerWait.h
* @brief プレイヤー待機処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerWaitクラス定義
	*/
	class PlayerWait : public PlayerActionState {
		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}