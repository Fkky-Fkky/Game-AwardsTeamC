#include "Classes/Enemy/Small Enemy/SmallEnemy.h"

void SmallEnemy::Initialize() {
    position_ = SimpleMath::Vector3(-3, 0, 0);
}

void SmallEnemy::LoadAssets() {
    model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Player/chara_mock.x");

    collision_ = model_->GetBoundingOrientedBox();
    collision_.Extents = SimpleMath::Vector3(
        collision_.Extents.x * 0.65f,
        collision_.Extents.y * 1.35f,
        collision_.Extents.z
    ) * 1.0f;

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

void SmallEnemy::Update(const float deltaTime) {
    collision_.Center = model_->GetPosition();
    collision_.Orientation = model_->GetRotationQuaternion();

    /*collision.BossCollision(collision_);*/
}

void SmallEnemy::Render() {
    model_->SetPosition(position_);
    model_->Draw();

    collision_model_->SetPosition(collision_.Center + SimpleMath::Vector3(0, 1.5f, 0));
    collision_model_->SetRotationQuaternion(collision_.Orientation);
    collision_model_->Draw();
}

