#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"

void BossBody::Initialize() {
	BossParts::Initialize(SimpleMath::Vector3(0.0f, 1.0f, 3.0f), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}
void BossBody::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss.X");
	model->SetScale(1.0f);
}

void BossBody::Render() {
	BossParts::Render();
}