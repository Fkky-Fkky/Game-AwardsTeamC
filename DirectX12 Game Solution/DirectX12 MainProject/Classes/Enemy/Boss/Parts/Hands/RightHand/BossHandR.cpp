#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"

void BossHandR::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, 0.0f),
		SimpleMath::Vector3(XM_PIDIV4, 5.0f, 0.0f)
	);
}

void BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}

void BossHandR::Update(const float deltaTime) {
	BossHand::Update(deltaTime);
}

void BossHandR::Render() {
	BossHand::Render();
}