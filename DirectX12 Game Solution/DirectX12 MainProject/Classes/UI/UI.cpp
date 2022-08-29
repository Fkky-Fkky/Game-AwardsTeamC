#include "Classes/UI/UI.h"
#include "Classes/Collision/ObjectManager.h"

UI::UI() {
	player_hp_width_ = 0.0f;
}

void UI::Initialize() {
	player_hp_width_ = PLAYER_HP_MAX_WIDTH_;
}

void UI::LoadAssets() {
	player_hp_top_	  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/line_001.png");
	player_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/line_002.png");
}

void UI::Update(const float deltaTime, ObjectManager* obj_m) {
	player_hp_width_ = obj_m->GetPlayerHP() * PLAYER_HP_WIDTH_DIVIDE_;
}

void UI::Render() {
	DX9::SpriteBatch->DrawSimple(
		player_hp_top_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, PLAYER_HP_TOP_POS_Z_),
		RectWH(0, 0, (int)player_hp_width_, PLAYER_HP_HIGHT_)
	);

	DX9::SpriteBatch->DrawSimple(
		player_hp_bottom_.Get(),
		SimpleMath::Vector3::Zero
	);
}