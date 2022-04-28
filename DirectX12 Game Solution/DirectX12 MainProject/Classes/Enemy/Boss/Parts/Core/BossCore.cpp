#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"

void BossCore::Initialize() {
	BossParts::Initialize(SimpleMath::Vector3(0.0f, 4.0f, 0.0f), SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
}
void BossCore::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_core.x");
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	model->SetMaterial(material);
}

void BossCore::Render() {
	BossParts::Render();
}