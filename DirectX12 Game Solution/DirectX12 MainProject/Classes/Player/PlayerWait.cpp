#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/Player.h"

void PlayerWait::Update(const float deltaTime, Player* const player) {
	if (DXTK->KeyEvent->pressed.W) {
		player->SwitchState(PLAYER_STATE::JUMP);
	}

	if (DXTK->KeyState->D) {
		player->SwitchState(PLAYER_STATE::RIGHT_MOVE);
	}

	if (DXTK->KeyState->A) {
		player->SwitchState(PLAYER_STATE::LEFT_MOVE);
	}

	if (DXTK->KeyEvent->pressed.Space) {
		player->SwitchState(PLAYER_STATE::ATTACK);
	}
}