#include "Classes/Player/PlayerColision.h"

void PlayerColision::LoadAssets(DX9::Model* model_) {
    collision_ = model_->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(
        collision_.Extents.x * EXTECTS_X_MULUTIPLY_VALUE_,
        collision_.Extents.y * EXTECTS_Y_MULUTIPLY_VALUE_,
        collision_.Extents.z
    );

    //デバッグ用↓
    collision_model_ = DX9::Model::CreateBox(
        DXTK->Device9,
        collision_.Extents.x,
        collision_.Extents.y,
        collision_.Extents.z
    );

    D3DMATERIAL9 material{};
    material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
    collision_model_->SetMaterial(material);
}

void PlayerColision::Update(const float deltaTime, DX9::Model* model_) {
    collision_.Center      = model_->GetPosition() + SimpleMath::Vector3(0, CENTER_PLUS_Y_VALUE_, 0);
    collision_.Orientation = model_->GetRotationQuaternion();
}

void PlayerColision::Render() {
    collision_model_->SetPosition(collision_.Center);
    collision_model_->SetRotationQuaternion(collision_.Orientation);
    collision_model_->Draw();
}