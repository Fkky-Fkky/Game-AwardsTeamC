#include "Classes/UI/UI.h"
#include "Classes/Collision/ObjectManager.h"

UI::UI() {

}

void UI::Initialize() {

}

void UI::LoadAssets() {
	player_hp_top_	  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/line_001.png");
	player_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/line_002.png");
}

void UI::Update(const float deltaTime, ObjectManager obj_m) {

}

void UI::Render() {
	DX9::SpriteBatch->DrawSimple(
		player_hp_top_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, -1.0f),
		RectWH(0, 0, PLAYER_HP_HIGHT, PLAYER_HP_HIGHT)
	);

	DX9::SpriteBatch->DrawSimple(
		player_hp_top_.Get(),
		SimpleMath::Vector3::Zero
	);
}