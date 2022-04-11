#include "Classes/Enemy/Boss/BossParts.h"

void BossParts::Initialize(float pos_x, float pos_y, float pos_z) {
	position = SimpleMath::Vector3(pos_x, pos_y, pos_z);
}
void BossParts::LoadAssets(LPCWSTR file_name) {
	model = DX9::Model::CreateFromFile(DXTK->Device9, file_name);
}
void BossParts::Update() {

}

void BossParts::Render() {
	model->SetPosition(position);
	model->Draw();
}