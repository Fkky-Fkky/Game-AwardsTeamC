#include "Classes/Player/Action/PlayerWait.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"
#include "Classes/Input/InputManager.h"

/**
* @brief 待機状態の更新
*
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
*/
void player::PlayerWait::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) {
	if (InputManager::GetInstance().IsInputJump()) {
		act_m->SwitchState(PLAYER_STATE::JUMP, player);
	}

	if (InputManager::GetInstance().IsInputRightMove()) {
		act_m->SwitchState(PLAYER_STATE::RIGHT_MOVE, player);
	}

	if (InputManager::GetInstance().IsInputLeftMove()) {
		act_m->SwitchState(PLAYER_STATE::LEFT_MOVE, player);
	}

	if (InputManager::GetInstance().IsInputAttack()) {
		act_m->SwitchState(PLAYER_STATE::ATTACK, player);
	}
}