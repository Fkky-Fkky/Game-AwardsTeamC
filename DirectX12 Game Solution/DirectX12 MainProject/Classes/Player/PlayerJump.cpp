#include "Classes/Player/PlayerJump.h"
#include "Base/DX12Effekseer.h"

PlayerJump::PlayerJump() {
    flag_ = false;
    time_ = 0.0f;
}

void PlayerJump::Update(const float deltaTime, SimpleMath::Vector3& pos_) {
    time_ += JUMP_TIME_SPEED_ * deltaTime;

    if (!flag_ && DXTK->KeyEvent->pressed.W) {
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
    }
}