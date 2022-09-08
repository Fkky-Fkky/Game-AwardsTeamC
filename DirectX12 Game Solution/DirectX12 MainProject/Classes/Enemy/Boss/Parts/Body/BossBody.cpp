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
	body_coll_ = model_->GetBoundingOrientedBox();
	body_coll_.Extents = SimpleMath::Vector3(
		body_coll_.Extents.x * COLLISION_SIZE_X_,
		body_coll_.Extents.y,
		body_coll_.Extents.z * COLLISION_SIZE_Z_
	);
	coll_model_ = DX9::Model::CreateBox(
		DXTK->Device9,
		body_coll_.Extents.x,
		body_coll_.Extents.y,
		body_coll_.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	coll_model_->SetMaterial(material);

	model_->SetTrackEnable(0, true);
}

void BossBody::Update(const float deltaTime, const ObjectManager* const obj_m_) {
	BossParts::Update(deltaTime);
	SimpleMath::Vector3 player_pos_ = obj_m_->GetPlayerPos();
	rotation.y = player_pos_.x * -1;
	body_coll_.Center = model_->GetPosition();
	body_coll_.Orientation = model_->GetRotationQuaternion();
}

void BossBody::Render() const {
	BossParts::Render();
	coll_model_->SetPosition(body_coll_.Center);
	coll_model_->SetRotationQuaternion(body_coll_.Orientation);
	coll_model_->Draw();
}