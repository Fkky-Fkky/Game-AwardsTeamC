#include "Classes/Player/Action/PlayerLeftMove.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"

/**
* @brief ���ړ��̍X�V
*
* @param[in] deltaTime ����
* @param[out] player �v���C���[
*/
void player::PlayerLeftMove::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) {
    SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
    SimpleMath::Vector3 rot_ = player->GetPlayerRotation();

    if (DXTK->KeyState->A) {
        pos_.x -= PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = PLAYER_ROTATION_ANGLE_;
    }
    else {
        act_m->SwitchState(PLAYER_STATE::WAIT, player);
    }

    pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);

    if (DXTK->KeyEvent->pressed.W) {
        act_m->SwitchState(PLAYER_STATE::JUMP, player);
    }

    if (DXTK->KeyEvent->pressed.Enter) {
        act_m->SwitchState(PLAYER_STATE::ATTACK, player);
    }

    player->SetPlayerPosition(pos_);
    player->SetPlayerRotation(rot_);
}