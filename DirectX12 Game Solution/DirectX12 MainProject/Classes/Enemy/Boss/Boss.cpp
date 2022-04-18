#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Player/Player.h"

Boss::Boss() {
	body_pos   = SimpleMath::Vector3::Zero;
}

void Boss::Initialize() {
	boss_attack.Initialize();
}

void Boss::LoadAseets(){
	boss_body = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss.X");
	body_pos = SimpleMath::Vector3(0.0f, 1.0f, 1.0f);

	boss_attack.LoadAssets();
}

void Boss::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {
	boss_attack.Update(deltaTime, player_pos);
}

void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();
	boss_attack.Render();
}