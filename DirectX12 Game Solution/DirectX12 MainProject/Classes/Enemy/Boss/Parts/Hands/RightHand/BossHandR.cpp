#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"

void BossHandR::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_POS_Z),
		SimpleMath::Vector3::Zero
	);
}

void BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}