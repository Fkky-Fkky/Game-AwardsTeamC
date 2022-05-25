#include "Classes/Player/PlayerJump.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Player/Player.h"

void PlayerJump::Update(const float deltaTime, Player& player) {
    SimpleMath::Vector3 pos_ = player.GetPlayerPosition();
    SimpleMath::Vector3 rot_ = player.GetPlayerRotation();

    if (!jump_flag_) {
        jump_flag_ = true;
        player_up_flag_ = true;
        jump_time_ = 0.0f;
        cool_time_ = 0.0f;
        DX12Effect.PlayOneShot("jump", pos_);
    }

    if (jump_flag_) {   //プレイヤージャンプ処理(上昇)
        if (player_up_flag_) {
            jump_time_ += deltaTime* DOWN_SPEED_;
            old_player_pos_ = pos_;
            pos_.y = -HALF_ * GRAVITY_ * jump_time_ * jump_time_ + V0_ * jump_time_ + GROUND_Y_;
            if (old_player_pos_.y >= pos_.y) {
                player_up_flag_ = false;
            }
        }
        else {  //プレイヤージャンプ処理(下降)
            jump_time_ += deltaTime;
            pos_.y = -HALF_ * GRAVITY_ * jump_time_ * jump_time_ + V0_ * jump_time_ + GROUND_Y_;
        }

        if (pos_.y <= GROUND_Y_) {
            pos_.y  = GROUND_Y_;
            cool_time_ += deltaTime;
            landing_flag_ = true;
            if (cool_time_ >= COOL_TIME_MAX_) {
                jump_flag_ = false;
                landing_flag_ = false;
                player.SwitchState(PLAYER_STATE::WAIT);
            }
        }
    }

    const bool is_player_right_ward_ = rot_.y < 0;

    if (!landing_flag_) {
        if (is_player_right_ward_) {
            if (DXTK->KeyState->D) {
                pos_.x += JUMPING_MOVE_ * deltaTime;
                rot_.y = -PLAYER_ROTATION_ANGLE_;
            }
        }
        else {
            if (DXTK->KeyState->A) {
                pos_.x -= JUMPING_MOVE_ * deltaTime;
                rot_.y = PLAYER_ROTATION_ANGLE_;
            }
        }
    }

    pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);

    player.SetPlayerPosition(pos_);
    player.SetPlayerRotation(rot_);
}