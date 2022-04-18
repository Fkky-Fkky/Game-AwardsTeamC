#include "Classes/Collision/Collision.h"

void Collision::Initialize() {
	hit_flg_ = false;
	hit_attack_flg_ = false;
}

void Collision::LoadAssets() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Collision::Update(const float deltaTime, bool attack_flag_, bool boss_r_attack_flag_, bool boss_l_attack_flag_) {
	if (boss_r_attack_flag_ || boss_l_attack_flag_) {
		hit_flg_ = player_collision_.Intersects(boss_hand_right_collision_) ||
				   player_collision_.Intersects(boss_hand_left_collision_);
	}
		

	if (attack_flag_)
		hit_attack_flg_ = player_attack_collision_.Intersects(core_collision_);
	else
		hit_attack_flg_ = false;
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

void Collision::PlayerAttackCollision(BoundingOrientedBox player_attack_) {
	player_attack_collision_ = player_attack_;
}

void Collision::BossHandRightCollision(BoundingOrientedBox boss_hand_right_) {
    boss_hand_right_collision_ = boss_hand_right_;
}

void Collision::BossHandLeftCollision(BoundingOrientedBox boss_hand_left_) {
	boss_hand_left_collision_ = boss_hand_left_;
}

void Collision::CoreCollision(BoundingOrientedBox core) {
	core_collision_ = core;
}
