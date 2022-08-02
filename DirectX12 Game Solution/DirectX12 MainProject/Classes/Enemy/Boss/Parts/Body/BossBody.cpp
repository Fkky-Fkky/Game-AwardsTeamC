#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"

void BossBody::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(0.0f, BODY_INIT_POS_Y_, 0.0f),
		SimpleMath::Vector3::Zero
	);
}

void BossBody::LoadAssets() {
	boss_body_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_head.x");
	boss_body_->SetScale(BODY_SCALE_);
	cube_coll_ = boss_body_->GetBoundingBox();
	cube_ = DX9::Model::CreateBox(
		DXTK->Device9,
		cube_coll_.Extents.x,
		cube_coll_.Extents.y,
		cube_coll_.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	cube_->SetMaterial(material);
}

void BossBody::Render() {
	boss_body_->SetPosition(position);
	boss_body_->SetRotation(XMConvertToRadians(rotation.x), XMConvertToRadians(rotation.y), XMConvertToRadians(rotation.z));
	boss_body_->Draw();

	cube_->Draw();
}