#include "Classes/Enemy/Small Enemy/SmallEnemy.h"

void SmallEnemy::Initialize() {
    position_ = SimpleMath::Vector3(-8, 0, 0);
    hit_flag_ = false;
    core_hp_ = 10;
}

void SmallEnemy::LoadAssets() {
    model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Player/chara_mock.x");
    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

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

    collision_2.Extents = SimpleMath::Vector3(
        collision_.Extents.x * 0.65f,
        collision_.Extents.y * 1.35f,
        collision_.Extents.z
    ) * 1.0f;

    collision_model_2 = DX9::Model::CreateBox(
        DXTK->Device9,
        collision_2.Extents.x,
        collision_2.Extents.y,
        collision_2.Extents.z
    );

    D3DMATERIAL9 material2{};
    material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
    collision_model_->SetMaterial(material2);
}

void SmallEnemy::Update(const float deltaTime) {
    collision_.Center = model_->GetPosition();
    collision_.Orientation = model_->GetRotationQuaternion();

    /*collision.BossCollision(collision_);*/
}

void SmallEnemy::Render() {
    //model_->SetPosition(position_);
    //model_->Draw();

    //collision_model_->SetPosition(collision_.Center + SimpleMath::Vector3(0, 1.5f, 0));
    //collision_model_->SetRotationQuaternion(collision_.Orientation);
    //collision_model_->Draw();

    collision_model_2->SetPosition(SimpleMath::Vector3(0, 1.5f, 0));
    collision_model_2->Draw();
}

void SmallEnemy::Render2D() {
    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 60.0f),
        DX9::Colors::Red,
        L"É{ÉX:%i", core_hp_
    );
}

void SmallEnemy::HitPlayerAttack(bool core_hit_flag_) {
    if (core_hit_flag_) {
        if (!hit_flag_)
            HitProcessing();
    }
    else {
        hit_flag_ = false;
    }
}

void SmallEnemy::HitProcessing() {
    core_hp_ -= 1;
    hit_flag_ = true;
}