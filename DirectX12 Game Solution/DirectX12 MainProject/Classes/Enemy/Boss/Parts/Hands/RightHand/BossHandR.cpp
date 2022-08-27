#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"

void BossHandR::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X_, INITIAL_POS_Y_, INITIAL_POS_Z_),
		SimpleMath::Vector3(INITIAL_ROT_X_, -INITIAL_ROT_Y_, 0.0f)
	);
}

void BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}