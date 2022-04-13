#include "Classes/Enemy/Boss/Boss.h"

Boss::Boss() {
	body_pos   = SimpleMath::Vector3::Zero;

	time_delta = 0.0f;
}

void Boss::Initialize() {
	time_delta = 0.0f;
	boss_attack.Initialize();
}

void Boss::LoadAseets(){
	boss_body = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss.X");
	body_pos = SimpleMath::Vector3(0.0f, 1.0f, 1.0f);


	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
	boss_attack.LoadAssets();
}

void Boss::Update(const float deltaTime) {
	time_delta = deltaTime;

	
	
	boss_attack.Update(deltaTime);
}

void Boss::Render2D() {
	if (boss_attack.GetHitFlag())
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚è"
		);
	else
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚ç‚È‚¢‚æ‚ÁI"
		);
}

void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();
	boss_attack.Render();
}