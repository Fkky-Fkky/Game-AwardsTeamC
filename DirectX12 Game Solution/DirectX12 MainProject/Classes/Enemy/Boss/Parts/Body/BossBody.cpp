#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"

void BossBody::Initialize() {
	BossParts::Initialize(SimpleMath::Vector3::Zero, SimpleMath::Vector3::Zero);
}
void BossBody::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_animation.X");
	model_->SetTrackEnable(0, true);
}