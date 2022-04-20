#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Player/Player.h"

Boss::Boss() {
	body_pos   = SimpleMath::Vector3::Zero;
}

void Boss::Initialize() {
	hand_l.Initialize();
	hand_r.Initialize();
}

void Boss::LoadAseets(){
	boss_body = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss.X");
	body_pos = SimpleMath::Vector3(0.0f, 1.0f, 1.0f);

	boss_core = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_core.x");
	core_pos = SimpleMath::Vector3(10.0f, 0.0f, 0.0f);
	hand_l.LoadAssets();
	hand_r.LoadAssets();
}

void Boss::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {
	hand_l.Update(deltaTime, player_pos);
	hand_r.Update(deltaTime, player_pos);
}

void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();

	boss_core->SetPosition(core_pos);
	boss_core->Draw();

	hand_l.Render();
	hand_r.Render();
}