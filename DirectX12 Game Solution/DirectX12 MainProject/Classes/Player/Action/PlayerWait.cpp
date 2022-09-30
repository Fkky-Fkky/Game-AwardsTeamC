#include "Classes/Player/Action/PlayerWait.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"

/**
* @brief �ҋ@��Ԃ̍X�V
*
* @param[in] deltaTime ����
* @param[out] player �v���C���[
*/
void player::PlayerWait::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) {
	if (DXTK->KeyEvent->pressed.W) {
		act_m->SwitchState(PLAYER_STATE::JUMP, player);
	}

	if (DXTK->KeyState->D) {
		act_m->SwitchState(PLAYER_STATE::RIGHT_MOVE, player);
	}

	if (DXTK->KeyState->A) {
		act_m->SwitchState(PLAYER_STATE::LEFT_MOVE, player);
	}

	if (DXTK->KeyEvent->pressed.Enter) {
		act_m->SwitchState(PLAYER_STATE::ATTACK, player);
	}
}