#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/Player.h"

/**
* @brief 値の初期化
*/
void player::PlayerJump::Initialize() {
    action_state_ = READY;
    time_delta_ = 0.0f;
    jump_time_  = 0.0f;
    cool_time_  = 0.0f;
    player_up_flag_ = false;
    pos_            = SimpleMath::Vector3::Zero;
    rot_            = SimpleMath::Vector3::Zero;
    old_player_pos_ = SimpleMath::Vector3::Zero;
}

/**
* @brief ジャンプ状態の更新
*
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
*/
void player::PlayerJump::Update(const float deltaTime, Player* const player) {
    pos_ = player->GetPlayerPosition();
    rot_ = player->GetPlayerRotation();

    time_delta_ = deltaTime;

    switch (action_state_) {
    case READY: Ready();        break;
    case JUMP:
        Jump(player);
        JumpingMove();          break;
    case COOL_TIME: CoolTime(); break;
    }
    

    player->SetPlayerPosition(pos_);
    player->SetPlayerRotation(rot_);
    if (action_state_ == ACTION_END) {
        action_state_ = READY;
        player->SwitchState(PLAYER_STATE::WAIT);
    }
}

/**
* @brief ジャンプに必要な変数の処理
*/
void player::PlayerJump::Ready() {
    player_up_flag_ = true;
    jump_time_      = 0.0f;
    action_state_   = JUMP;
}

/**
* @brief ジャンプ
* 
* @param[out] プレイヤー
*/
void player::PlayerJump::Jump(Player* const player) {
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
        player->SetMotion(PLAYER_MOTION::JUMP);
        action_state_ = COOL_TIME;
    }
}

/**
* @brief クールタイム
*/
void player::PlayerJump::CoolTime() {
    cool_time_ = std::min(cool_time_ += time_delta_, COOL_TIME_MAX_);
    if (cool_time_ >= COOL_TIME_MAX_) {
        cool_time_ = 0.0f;
        action_state_ = ACTION_END;
    }
}

/**
* @brief ジャンプ中の移動処理
*/
void player::PlayerJump::JumpingMove() {
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