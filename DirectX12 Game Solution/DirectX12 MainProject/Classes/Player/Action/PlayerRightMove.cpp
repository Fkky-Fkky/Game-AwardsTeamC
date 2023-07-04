#include "Classes/Player/Action/PlayerRightMove.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"

/**
* @brief 右移動の更新
*
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
*/
void player::PlayerRightMove::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) {
    SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
    SimpleMath::Vector3 rot_ = player->GetPlayerRotation();

    if (DXTK->KeyState->D ||
        DXTK->GamePadState->thumbSticks.leftX > 0) {
        pos_.x += PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = -PLAYER_ROTATION_ANGLE_;
    }
    else {
        act_m->SwitchState(PLAYER_STATE::WAIT, player);
    }

    pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);

    if (DXTK->KeyEvent->pressed.W ||
        DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED) {
        act_m->SwitchState(PLAYER_STATE::JUMP, player);
    }

    if (DXTK->KeyEvent->pressed.Enter ||
        DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED) {
        act_m->SwitchState(PLAYER_STATE::ATTACK, player);
    }

    player->SetPlayerPosition(pos_);
    player->SetPlayerRotation(rot_);
}