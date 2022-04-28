#include "Classes/Player/PlayerAttackColision.h"

void PlayerAttackColision::LoadAssets(DX9::Model* model_) {
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

void PlayerAttackColision::Update(const float deltaTime, DX9::Model* model_) {
    collision_.Center = model_->GetPosition() + SimpleMath::Vector3(0, 1.5f, 0);
    collision_.Orientation = model_->GetRotationQuaternion();
}

void PlayerAttackColision::Render() {
    collision_model_->SetPosition(collision_.Center);
    collision_model_->SetRotationQuaternion(collision_.Orientation);
    collision_model_->Draw();
}