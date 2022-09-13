#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"

void BossHandL::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X_, INITIAL_POS_Y_, INITIAL_POS_Z_),
		SimpleMath::Vector3(INITIAL_ROT_X_, INITIAL_ROT_Y_, 0.0f)
	);
}

void BossHandL::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_L.X");
}

void BossHandL::Update(const float deltaTime) {
	BossHand::Update(deltaTime);
	collision.Center	  = model_->GetPosition() + SimpleMath::Vector3(ADD_COLLISION_POS_X_, 0.0f, 0.0f);
	collision.Orientation = model_->GetRotationQuaternion();
}