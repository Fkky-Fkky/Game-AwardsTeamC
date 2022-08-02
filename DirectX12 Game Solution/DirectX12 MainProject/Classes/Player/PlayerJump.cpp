#include "Classes/Player/PlayerJump.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Player/Player.h"

void PlayerJump::Initialize() {
    action_state_ = READY;
    time_delta_ = 0.0f;
    jump_time_  = 0.0f;
    cool_time_  = 0.0f;
    player_up_flag_ = false;
    pos_            = SimpleMath::Vector3::Zero;
    rot_            = SimpleMath::Vector3::Zero;
    old_player_pos_ = SimpleMath::Vector3::Zero;
}

void PlayerJump::Update(const float deltaTime, Player& player) {
    pos_ = player.GetPlayerPosition();
    rot_ = player.GetPlayerRotation();

    time_delta_ = deltaTime;

    switch (action_state_) {
    case READY: Ready(player);  break;
    case JUMP:
        Jump();
        JumpingMove();          break;
    case COOL_TIME: CoolTime(); break;
    }
    

    player.SetPlayerPosition(pos_);
    player.SetPlayerRotation(rot_);
    if (action_state_ == ACTION_END) {
        action_state_ = READY;
        player.SwitchState(PLAYER_STATE::WAIT);
    }
}

void PlayerJump::Ready(Player& player) {  //ジャンプに必要な変数の処理
    DX12Effect.PlayOneShot("jump", pos_);
    player_up_flag_ = true;
    jump_time_      = 0.0f;
    player.PlayJumpSE();
    action_state_   = JUMP;
}

void PlayerJump::Jump() {   //ジャンプ
    if (player_up_flag_) {  //プレイヤージャンプ処理(上昇)
        jump_time_ += time_delta_ * DOWN_SPEED_;
        old_player_pos_ = pos_;
        pos_.y = -HALF_ * GRAVITY_ * jump_time_ * jump_time_ + V0_ * jump_time_ + GROUND_Y_;
        if (old_player_pos_.y >= pos_.y) {
            player_up_flag_ = false;
        }
    }
    else {  //プレイヤージャンプ処理(下降)
        jump_time_ += time_delta_ * DOWN_SPEED_;
        pos_.y = -HALF_ * GRAVITY_ * jump_time_ * jump_time_ + V0_ * jump_time_ + GROUND_Y_;
    }

    if (pos_.y <= GROUND_Y_) {
        pos_.y  = GROUND_Y_;
        action_state_ = COOL_TIME;
    }
}

void PlayerJump::CoolTime() {   //クールタイム
    cool_time_ += time_delta_;

    if (cool_time_ >= COOL_TIME_MAX_) {
        cool_time_ = 0.0f;
        action_state_ = ACTION_END;
    }
}

void PlayerJump::JumpingMove() {    //ジャンプ中の移動処理
    const bool is_player_right_ward_ = rot_.y < 0;

    if (is_player_right_ward_) {
        if (DXTK->KeyState->D) {
            pos_.x += JUMPING_MOVE_SPEED_ * time_delta_;
            rot_.y = -PLAYER_ROTATION_ANGLE_;
        }
        if (DXTK->KeyState->A) {
            pos_.x -= JUMPING_MOVE_SPEED_REVERSE * time_delta_;
        }
    }
    else {
        if (DXTK->KeyState->A) {
            pos_.x -= JUMPING_MOVE_SPEED_ * time_delta_;
            rot_.y = PLAYER_ROTATION_ANGLE_;
        }
        if (DXTK->KeyState->D) {
            pos_.x += JUMPING_MOVE_SPEED_REVERSE * time_delta_;
        }
    }
    pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);
}