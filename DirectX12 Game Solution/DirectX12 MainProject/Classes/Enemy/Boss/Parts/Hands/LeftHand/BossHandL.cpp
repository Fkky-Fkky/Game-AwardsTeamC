#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"

void BossHandL::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, INITIAL_POS_Z),
		SimpleMath::Vector3::Zero
	);
}

void BossHandL::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_L.X");
}