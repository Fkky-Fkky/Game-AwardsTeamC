#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Collision/ObjectManager.h"

void BossBody::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(0.0f, BODY_INIT_POS_Y_, BODY_INIT_POS_Z_),
		SimpleMath::Vector3(BODY_INIT_ROT_X_, 0.0f, 0.0f)
	);
}

void BossBody::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_head.x");
	model_->SetScale(BODY_SCALE_);
	cube_coll_ = model_->GetBoundingBox();
	cube_ = DX9::Model::CreateBox(
		DXTK->Device9,
		cube_coll_.Extents.x,
		cube_coll_.Extents.y,
		cube_coll_.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	cube_->SetMaterial(material);

	model_->SetTrackEnable(0, true);
}

void BossBody::Update(const float deltaTime, ObjectManager* obj_m_) {
	BossParts::Update(deltaTime);
	SimpleMath::Vector3 player_pos_ = obj_m_->GetPlayerPos();
	rotation.y = player_pos_.x * -1;
}

void BossBody::Render() {
	BossParts::Render();
	cube_->SetPosition(position);
	cube_->SetRotation(rotation);
	//cube_->Draw();
}