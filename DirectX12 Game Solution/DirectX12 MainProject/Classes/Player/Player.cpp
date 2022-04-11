#include "Classes/Player/Player.h"

void Player::Initialize() {
	pos_player_ = SimpleMath::Vector3(0, 0, 0);
	rot_player_ = SimpleMath::Vector3(0, 0, 0);
}

void Player::LoadAssets() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Player/chara_mock.x");
	stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/stage_a.X");
}

void Player::Update(const float deltaTime) {

}

void Player::Render() {
	model_->SetPosition(pos_player_);
	model_->SetRotation(rot_player_);
	model_->Draw();
}