#include "Classes/Enemy/Boss/Parts/BossParts.h"

void BossParts::Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote) {
	position = pos;
	rotation = rote;
}

void BossParts::LoadAssets(LPCWSTR file_name) {
	model = DX9::Model::CreateFromFile(DXTK->Device9, file_name);
}

void BossParts::Render() {
	model->SetPosition(position);
	model->SetRotation(rotation);
	model->Draw();
}