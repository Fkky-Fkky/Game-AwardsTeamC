#include "Classes/Player/PlayerAttackColision.h"
#include <Base/DX12Effekseer.h>
#include "Classes/Player/Player.h"

void player::PlayerAttackColision::Initialize() {
    attack_time_ = 0.0f;
    is_player_attack_ = false;
    is_effect_play_   = false;
    is_se_play_ = false;
}

void player::PlayerAttackColision::LoadAssets(DX9::SkinnedModel* const model_) {
    collision_ = model_->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(   //当たり判定のサイズ調整
        collision_.Extents.x * COLLISION_SIZE_MULTIPLY_X_,
        collision_.Extents.y * COLLISION_SIZE_MULTIPLY_Y_,
        collision_.Extents.z * COLLISION_SIZE_MULTIPLY_Z_
    );
}

void player::PlayerAttackColision::Update(const float deltaTime, const DX9::SkinnedModel* const model_, const Player* const player) {
    float player_angle_             = player->GetPlayerRotation().y;
    bool  is_player_attack_start_   = player->IsPlayerAttackStart();
    bool  is_player_right_ward_     = player_angle_ == RIGHT_;
    float effect_angle_             = (is_player_right_ward_) ? RIGHT_ANGLE_ : LEFT_ANGLE_;
    SimpleMath::Vector3 player_pos_ = player->GetPlayerPosition();

    if (is_player_attack_start_) {
        attack_time_ = std::min(attack_time_ + deltaTime, MAX_ATTACK_TIME_);
        if (!is_effect_play_) {
            is_effect_play_ = true;
            DX12Effect.PlayOneShot("swaord", player_pos_);
            DX12Effect.SetRotation("swaord", SimpleMath::Vector3(0.0f, XMConvertToRadians(effect_angle_), 0.0f));
        }
        AtkProcess(player);
    }
    else
    {
        attack_time_      = 0.0f;
        is_player_attack_ = false;
        is_se_play_ = false;
        if (is_effect_play_) {
            is_effect_play_ = false;
            DX12Effect.Stop("swaord");
        }
    }
    float attack_x_ = (is_player_right_ward_) ? ATTACK_DISTANCE_X_ : -ATTACK_DISTANCE_X_;
    collision_.Center = player_pos_ + SimpleMath::Vector3(attack_x_, ATTACK_DISTANCE_Y_, 0.0f);
    collision_.Orientation = model_->GetRotationQuaternion();
}

void player::PlayerAttackColision::AtkProcess(const Player* const player) {
    if (attack_time_ >= ATTACK_START_TIME_) {
        is_player_attack_ = true;
        if (!is_se_play_) {
            player->PlayAtkSE();
            is_se_play_ = true;
        }
    }
    if (attack_time_ >= ATTACK_END_TIME_) {
        is_player_attack_ = false;
    }
}