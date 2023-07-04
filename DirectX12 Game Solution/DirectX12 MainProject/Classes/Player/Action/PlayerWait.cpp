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
	if (DXTK->KeyEvent->pressed.W ||
		DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
		act_m->SwitchState(PLAYER_STATE::JUMP, player);
	}

	if (DXTK->KeyState->D || 
		DXTK->GamePadState->thumbSticks.leftX > 0) {
		act_m->SwitchState(PLAYER_STATE::RIGHT_MOVE, player);
	}

	if (DXTK->KeyState->A ||
		DXTK->GamePadState->thumbSticks.leftX < 0) {
		act_m->SwitchState(PLAYER_STATE::LEFT_MOVE, player);
	}

	if (DXTK->KeyEvent->pressed.Enter ||
		DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED) {
		act_m->SwitchState(PLAYER_STATE::ATTACK, player);
	}
}