#include "Classes/Player/PlayerJump.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Player/Player.h"

PlayerJump::PlayerJump() {
    flag_ = false;
    time_ = 0.0f;
}

void PlayerJump::Update(const float deltaTime, Player& player) {
    SimpleMath::Vector3 pos_ = player.GetPlayerPosition();
    SimpleMath::Vector3 rot_ = player.GetPlayerRotation();

    time_ += JUMP_TIME_SPEED_ * deltaTime;

    if (!flag_) {
        flag_ = true;
        time_ = 0.0f;
        DX12Effect.PlayOneShot("jump", pos_);
    }

    if (flag_) {
        pos_.y = -HALF_ * GRAVITY_ * time_ * time_ + V0_ * time_ + GROUND_Y_;
    }

    if (pos_.y < GROUND_Y_) {
        pos_.y = GROUND_Y_;
        flag_ = false;
        player.SwitchState(PLAYER_STATE::WAIT);
    }

    if (DXTK->KeyState->D) {
        pos_.x += PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = -PLAYER_ROTATION_ANGLE_;
    }

    if (DXTK->KeyState->A) {
        pos_.x -= PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = PLAYER_ROTATION_ANGLE_;
    }

    player.SetPlayerPosition(pos_);
    player.SetPlayerRotation(rot_);
}