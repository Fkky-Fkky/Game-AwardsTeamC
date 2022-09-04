#include "Classes/UI/UI.h"
#include "Classes/Collision/ObjectManager.h"

UI::UI() {
	player_hp_width_ = 0.0f;
	boss_hp_width_ = 0.0f;
	player_hp_pos_ = SimpleMath::Vector3::Zero;
	boss_hp_pos_ = SimpleMath::Vector3::Zero;
}

void UI::Initialize() {
	player_hp_width_ = PLAYER_HP_MAX_WIDTH_;
	boss_hp_width_ = BOSS_HP_MAX_WIDTH_;
	player_hp_pos_ = SimpleMath::Vector3(PLAYER_HP_POS_X_, PLAYER_HP_POS_Y_, 0.0f);
	boss_hp_pos_ = SimpleMath::Vector3(BOSS_HP_POS_X_, BOSS_HP_POS_Y_, 0.0f);
}

void UI::LoadAssets() {
	player_hp_top_	  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_max.png");
	player_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_min.png");
	boss_hp_top_	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_max.png");
	boss_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_min.png");
}

void UI::Update(const float deltaTime, ObjectManager* obj_m) {
	player_hp_width_ = obj_m->GetPlayerHP() * PLAYER_HP_WIDTH_DIVIDE_;
	boss_hp_width_   = obj_m->GetBossHP()	* BOSS_HP_WIDTH_DIVIDE_;
}

void UI::Render() {
	DX9::SpriteBatch->DrawSimple(
		player_hp_bottom_.Get(),
		SimpleMath::Vector3(player_hp_pos_)
	);

	DX9::SpriteBatch->DrawSimple(
		player_hp_top_.Get(),
		SimpleMath::Vector3(player_hp_pos_),
		RectWH(0, 0, (int)player_hp_width_, PLAYER_HP_HIGHT_)
	);

	DX9::SpriteBatch->DrawSimple(
		boss_hp_bottom_.Get(),
		SimpleMath::Vector3(boss_hp_pos_)
	);

	DX9::SpriteBatch->DrawSimple(
		boss_hp_top_.Get(),
		SimpleMath::Vector3(boss_hp_pos_),
		RectWH(0, 0, (int)boss_hp_width_, BOSS_HP_HIGHT_)
	);
}