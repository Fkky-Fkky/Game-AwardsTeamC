#include "Classes/Player/PlayerJump.h"
#include "Base/DX12Effekseer.h"

PlayerJump::PlayerJump() {
    flag_ = false;
    time_ = 0.0f;
}

void PlayerJump::Update(const float deltaTime, SimpleMath::Vector3& pos_) {
    time_ += 1.0f;

    if (!flag_ && DXTK->KeyEvent->pressed.W) {
        flag_ = true;
        time_ = 0.0f;
        DX12Effect.PlayOneShot("jump", pos_);
    }

    if (flag_) {
        pos_.y = -0.5 * GRAVITY_ * time_ * time_ + V0_ * time_ + GROUND_Y_;
    }

    if (pos_.y < GROUND_Y_) {
        pos_.y = GROUND_Y_;
        flag_ = false;
    }
}