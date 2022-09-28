#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/Player.h"

/**
* @brief �ҋ@��Ԃ̍X�V
*
* @param[in] deltaTime ����
* @param[out] player �v���C���[
*/
void player::PlayerWait::Update(const float deltaTime, Player* const player) {
	if (DXTK->KeyEvent->pressed.W) {
		player->SwitchState(PLAYER_STATE::JUMP);
	}

	if (DXTK->KeyState->D) {
		player->SwitchState(PLAYER_STATE::RIGHT_MOVE);
	}

	if (DXTK->KeyState->A) {
		player->SwitchState(PLAYER_STATE::LEFT_MOVE);
	}

	if (DXTK->KeyEvent->pressed.Enter) {
		player->SwitchState(PLAYER_STATE::ATTACK);
	}
}