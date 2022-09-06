#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"
#include "Classes/Enemy/Boss/Boss.h"

void BossCore::Initialize() {
	core_pos_.y = CORE_INTIAL_POS_Y_;
	core_pos_.z = CORE_INTIAL_POS_Z_;
	BossParts::Initialize(core_pos_, SimpleMath::Vector3::Zero);
	core_hp_  = BOSS_MAX_HP_;
	time_delta_ = 0.0f;
	core_weak_time_ = 0.0f;
	hit_flag_ = false;
}

void BossCore::LoadAssets() {
	core_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_Core.X");
	
	collision_ = core_->GetBoundingOrientedBox();
	collision_.Extents = SimpleMath::Vector3(
		collision_.Extents.x * 0.5f,
		collision_.Extents.y * 0.5f,
		collision_.Extents.z * 0.5f
	);

	collision_model_ = DX9::Model::CreateBox(
		DXTK->Device9,
		collision_.Extents.x,
		collision_.Extents.y,
		collision_.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 0.0f, 1.0f, 0.75f);
	collision_model_->SetMaterial(material);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

	hit_efc_ = DX12Effect.Create(L"Effect/Eff_BossHit/Eff_bossHit.efk");
}

void BossCore::Update(const float deltaTime, const bool core_hit_flag, const Boss* boss) {
	time_delta_ = deltaTime;
	collision_.Center	   = core_->GetPosition();
	collision_.Orientation = core_->GetRotationQuaternion();
	CoreMove(boss->IsBossWeak());
	HitPlayerAttack(core_hit_flag);
}

void BossCore::Render() const {
	core_->SetPosition(position);
	core_->SetRotation(rotation);
	core_->Draw();

	collision_model_->SetPosition(collision_.Center);
	collision_model_->SetRotationQuaternion(collision_.Orientation);
	collision_model_->Draw();
}

void BossCore::Render2D() const {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(0.0f, 60.0f),
		DX9::Colors::Red,
		L"É{ÉX:%f", core_hp_
	);
}

void BossCore::CoreMove(bool weak_state){
	if (weak_state) {
		position.y = std::min(position.y + CORE_MOVE_SPEED_Y_ * time_delta_, CORE_MOVE_DEST_Y_);
	}
	else {
		position.y = std::max(position.y - CORE_MOVE_SPEED_Y_ * time_delta_, CORE_INTIAL_POS_Y_);
	}
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
	DX12Effect.Play(hit_efc_, position);
	hit_flag_ = true;
}