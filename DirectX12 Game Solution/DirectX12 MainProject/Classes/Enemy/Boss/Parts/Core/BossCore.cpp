#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"

void BossCore::Initialize() {
	core_pos_.y = BOSS_CORE_POS_Y_;
	BossParts::Initialize(core_pos_, SimpleMath::Vector3::Zero);
	core_hp_  = BOSS_MAX_HP_;
	hit_flag_ = false;
}

void BossCore::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_core.x");
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	model->SetMaterial(material);

	collision_ = model->GetBoundingOrientedBox();
	collision_.Extents = SimpleMath::Vector3(collision_.Extents);

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	hit_efc_ = DX12Effect.Create(L"Effect/Eff_BossHit/Eff_bossHit.efk");
}

void BossCore::Update(const float deltaTime, bool core_hit_flag) {
	collision_.Center	   = model->GetPosition();
	collision_.Orientation = model->GetRotationQuaternion();
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
	core_hp_--;
	DX12Effect.Play(hit_efc_, core_pos_);
	hit_flag_ = true;
}