#include "Classes/Collision/Collision.h"

void Collision::Initialize() {
	hit_flg_ = false;
}

void Collision::LoadAssets() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Collision::Update(const float deltaTime) {
    hit_flg_ = player_collision_.Intersects(boss_collision_);
}

void Collision::Render() {
    
}

void Collision::Render2D() {
	if (hit_flg_)
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚Á‚Ä‚é"
		);
	else
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚Á‚Ä‚È‚¢"
		);
}

void Collision::PlayerCollision(BoundingOrientedBox player) {
    player_collision_ = player;
}

void Collision::BossCollision(BoundingOrientedBox boss) {
    boss_collision_ = boss;
}
