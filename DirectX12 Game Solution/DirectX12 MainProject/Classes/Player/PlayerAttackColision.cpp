#include "Classes/Player/PlayerAttackColision.h"
#include <Base/DX12Effekseer.h>
#include "Classes/Player/Player.h"

void PlayerAttackColision::LoadAssets(DX9::SkinnedModel* model_) {
    collision_ = model_->GetBoundingOrientedBox();
    collision_.Extents = SimpleMath::Vector3(collision_.Extents);

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
    if (!attack_flg_ && DXTK->KeyEvent->pressed.Space) {
        attack_flg_ = true;
        DX12Effect.PlayOneShot("swaord", model_->GetPosition());
        //DX12Effect.SetRotation("swaord", SimpleMath::Vector3(0.0f, DirectX::XMConvertToRadians(0.0f), 0.0f));
        
    }

    if (attack_flg_) {
        attack_time_ += deltaTime;
        player->SetMotion(PLAYER_MOTION::ATTACK);

        if (attack_time_ > MAX_ATTACK_TIME_) {
            attack_time_ = 0.0f;
            attack_flg_  = false;
            player->SetMotion(PLAYER_MOTION::WAIT);
        }
    }

    float player_angle_ = DirectX::XMConvertToRadians(model_->GetRotation().z);
    float attack_x_ = (player_angle_ < 0.0f) ? ATTACK_DISTANCE_X_ : -ATTACK_DISTANCE_X_;
    collision_.Center = model_->GetPosition() + SimpleMath::Vector3(attack_x_, ATTACK_DISTANCE_Y_, 0.0f);
    collision_.Orientation = model_->GetRotationQuaternion();
}

void PlayerAttackColision::Render() {
    if (attack_flg_) {
        collision_model_->SetPosition(collision_.Center);
        collision_model_->SetRotationQuaternion(collision_.Orientation);
        collision_model_->Draw();
    }
}