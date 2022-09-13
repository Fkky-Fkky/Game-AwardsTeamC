#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/Player.h"

void PlayerLeftMove::Update(const float deltaTime, Player* const player) {
    SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
    SimpleMath::Vector3 rot_ = player->GetPlayerRotation();

    if (DXTK->KeyState->A) {
        pos_.x -= PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = PLAYER_ROTATION_ANGLE_;
    }
    else {
        player->SwitchState(PLAYER_STATE::WAIT);
    }

    pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);

    if (DXTK->KeyEvent->pressed.W) {
        player->SwitchState(PLAYER_STATE::JUMP);
    }

    if (DXTK->KeyEvent->pressed.Space) {
        player->SwitchState(PLAYER_STATE::ATTACK);
    }

    player->SetPlayerPosition(pos_);
    player->SetPlayerRotation(rot_);
}