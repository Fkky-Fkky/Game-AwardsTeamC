#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"

void BossHandL::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_POS_Z),
		SimpleMath::Vector3(XM_PIDIV4, -5.0f, 0.0f)
	);
}

void BossHandL::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_L.X");
	hand_l_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Boss/boss_hand_L.X");
	
	collision = hand_l_->GetBoundingOrientedBox();
	collision.Extents = SimpleMath::Vector3(
		collision.Extents.x * 0.5f,
		collision.Extents.y * 0.3f,
		collision.Extents.z * 0.3f
	);

	collision_model = DX9::Model::CreateBox(
		DXTK->Device9,
		collision.Extents.x,
		collision.Extents.y,
		collision.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	collision_model->SetMaterial(material);

	for (int i = 0; i < 2; ++i) {
		hand_l_->SetTrackEnable(i, false);
	}
	hand_l_->SetTrackEnable(1, true);
}

void BossHandL::Update(const float deltaTime) {
	hand_l_->AdvanceTime(deltaTime);
	collision.Center = hand_l_->GetPosition();
	collision.Orientation = hand_l_->GetRotationQuaternion();
}

void BossHandL::Render() {
	hand_l_->SetPosition(position);
	hand_l_->SetRotation(rotation);
	hand_l_->Draw();

	collision_model->SetPosition(collision.Center);
	collision_model->SetRotationQuaternion(collision.Orientation);
	collision_model->Draw();
}