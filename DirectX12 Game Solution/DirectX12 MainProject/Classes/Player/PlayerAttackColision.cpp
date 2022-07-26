#include "Classes/Player/PlayerAttackColision.h"
#include <Base/DX12Effekseer.h>
#include "Classes/Player/Player.h"

void PlayerAttackColision::Initialize() {
    attack_flg_ = false;
    attack_time_ = 0.0f;
}

void PlayerAttackColision::LoadAssets(DX9::SkinnedModel* model_) {
    collision_ = model_->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(   //当たり判定のサイズ調整
        collision_.Extents.x * COLLISION_SIZE_MULTIPLY_X_,
        collision_.Extents.y * COLLISION_SIZE_MULTIPLY_Y_,
        collision_.Extents.z * COLLISION_SIZE_MULTIPLY_Z_
    );

    //デバッグ用
    collision_model_ = DX9::Model::CreateBox(
        DXTK->Device9,
        collision_.Extents.x,
        collision_.Extents.y,
        collision_.Extents.z
    );

    D3DMATERIAL9 material_{};
    material_.Diffuse = DX9::Colors::Value(0.0f, 0.0f, 1.0f, 0.75f);
    collision_model_->SetMaterial(material_);
}

void PlayerAttackColision::Update(const float deltaTime, DX9::SkinnedModel* model_, Player* player) {
    if (player->GetPlayerState() == PLAYER_STATE::DAMAGE) {
        Initialize();
        model_->SetTrackPosition((int)PLAYER_MOTION::ATTACK, 0);
        return;
    }
    SimpleMath::Vector3 player_pos_ = player->GetPlayerPosition();
    float player_angle_ = player->GetPlayerRotation().y;
    bool is_player_right_ward_ = player_angle_ == RIGHT_;

    float effect_pos_x_ = (is_player_right_ward_) ? ADD_POS_X_ : -ADD_POS_X_;
    float effect_angle_ = (is_player_right_ward_) ? RIGHT_ANGLE_ : LEFT_ANGLE_;

    if (!attack_start_flag_ && DXTK->KeyEvent->pressed.Space) {
        attack_start_flag_ = true;
        player->SetMotion(PLAYER_MOTION::ATTACK);
    }

    if (attack_start_flag_) {
        attack_time_ += deltaTime;

        if (attack_time_ >= 0.65f && !is_effect_play_) {
            DX12Effect.PlayOneShot("swaord", player_pos_);
            is_effect_play_ = true;
            DX12Effect.SetRotation("swaord", SimpleMath::Vector3(0.0f, XMConvertToRadians(effect_angle_), 0.0f));
        }

        if (attack_time_ >= 1.3f) {
            attack_flg_ = true;
        }

        if (attack_time_ > MAX_ATTACK_TIME_) {
            attack_time_ = 0.0f;
            attack_start_flag_ = false;
            attack_flg_  = false;
            is_effect_play_ = false;
            player->SwitchState(PLAYER_STATE::WAIT);
            //player->SetMotion(PLAYER_MOTION::WAIT);
        }
    }
    float attack_x_ = (is_player_right_ward_) ? ATTACK_DISTANCE_X_ : -ATTACK_DISTANCE_X_;
    collision_.Center = player_pos_ + SimpleMath::Vector3(attack_x_, ATTACK_DISTANCE_Y_, 0.0f);
    collision_.Orientation = model_->GetRotationQuaternion();
}

void PlayerAttackColision::Render() {
    if (attack_flg_) {
        collision_model_->SetPosition(collision_.Center);
        collision_model_->SetRotationQuaternion(collision_.Orientation);
        collision_model_->Draw();
    }
}