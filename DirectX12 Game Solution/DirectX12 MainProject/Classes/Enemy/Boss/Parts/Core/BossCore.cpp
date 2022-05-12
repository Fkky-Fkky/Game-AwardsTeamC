#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"

BossCore::BossCore()
{
	core_hp_ = 0;
	hit_flag_ = false;
}

void BossCore::Initialize() {
	BossParts::Initialize(SimpleMath::Vector3(0.0f, 0.0f, 0.0f), SimpleMath::Vector3::Zero);
	core_hp_ = 30;
	hit_flag_ = false;
}
void BossCore::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_core.x");
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	model->SetMaterial(material);

	collision = model->GetBoundingOrientedBox();
	collision.Extents = SimpleMath::Vector3(collision.Extents);

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void BossCore::Update(const float deltaTime, bool core_hit_flag) {
	collision.Center = model->GetPosition();
	collision.Orientation = model->GetRotationQuaternion();
	HitPlayerAttack(core_hit_flag);
}

void BossCore::Render2D() {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 60.0f),
		DX9::Colors::Red,
		L"É{ÉX:%i", core_hp_
	);
}

void BossCore::HitPlayerAttack(bool core_hit_flag) {
	if (core_hit_flag) {
		if (!hit_flag_)
			HitProcessing();
	}
	else {
		hit_flag_ = false;
	}
}

void BossCore::HitProcessing() {
	core_hp_ -= 1;
	hit_flag_ = true;
}