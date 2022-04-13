#include "Classes/Enemy/Boss/Boss.h"

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

void Boss::Update(const float deltaTime) {	
	boss_attack.Update(deltaTime);
}

void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();
	boss_attack.Render();
}