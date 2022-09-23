#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"

void boss::BossHandR::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X_, INITIAL_POS_Y_, INITIAL_POS_Z_),
		SimpleMath::Vector3(INITIAL_ROT_X_, -INITIAL_ROT_Y_, 0.0f)
	);
}

void boss::BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}

void boss::BossHandR::Update(const float deltaTime) {
	BossHand::Update(deltaTime);
	collision_.Center	  = model_->GetPosition() + SimpleMath::Vector3(ADD_COLLISION_POS_X_, 0.0f, 0.0f);
	collision_.Orientation = model_->GetRotationQuaternion();
}