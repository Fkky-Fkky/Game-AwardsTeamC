#include "Classes/Enemy/Boss/Parts/BossParts.h"

void BossParts::Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote) {
	position = pos;
	rotation = rote;
}

void BossParts::LoadAssets(LPCWSTR file_name) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name);
}

void BossParts::Update(const float deltaTime) {
	model_->AdvanceTime(deltaTime);
}

void BossParts::Render() {
	model_->SetPosition(position);
	model_->SetRotation(
		XMConvertToRadians(rotation.x),
		XMConvertToRadians(rotation.y),
		XMConvertToRadians(rotation.z)
	);
	model_->Draw();
}