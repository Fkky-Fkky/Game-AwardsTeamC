#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"

void BossBody::Initialize() {
	BossParts::Initialize(SimpleMath::Vector3(0.0f, 0.0f, 8.0f), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}
void BossBody::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss.X");
}