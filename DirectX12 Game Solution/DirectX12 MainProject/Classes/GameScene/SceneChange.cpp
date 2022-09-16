#include "Classes/GameScene/SceneChange.h"
#include "Classes/Collision/ObjectManager.h"

void SceneChange::Initialize() {
	black_alpha_ = COLOR_MAX_;
	white_alpha_ = 0.0f;
	wait_time_	 = 0.0f;
	is_game_start_ = false;
	is_game_clear_ = false;
	scene_change_flag_ = false;
}

void SceneChange::LoadAssets() {
	black_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Black.png");
	white_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/White.png");
}

void SceneChange::Update(const float deltaTime, ObjectManager* obj_m) {
	if (!is_game_start_) {
		black_alpha_ = std::max(black_alpha_ - ALPHA_SPEED_ * deltaTime, 0.0f);
		is_game_start_ = black_alpha_ <= 0.0f;
	}

	if (obj_m->IsBossDeath()) {
		wait_time_ = std::min(wait_time_ + deltaTime, WAIT_TIME_MAX_);
	}
	if (wait_time_ >= WAIT_TIME_MAX_) {
		white_alpha_ = std::min(white_alpha_ + ALPHA_SPEED_ * deltaTime, COLOR_MAX_);
		scene_change_flag_ = white_alpha_ >= COLOR_MAX_;
		is_game_clear_ = true;
	}

	if (obj_m->GetPlayerHP() <= 0.0f) {
		black_alpha_ = std::min(black_alpha_ + ALPHA_SPEED_ * deltaTime, COLOR_MAX_);
		scene_change_flag_ = black_alpha_ >= COLOR_MAX_;
	}
}

void SceneChange::Render2D() {
	DX9::SpriteBatch->DrawSimple(
		black_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, SPRITE_POS_Z_),
		RectWH(0, 0, WIDTH_MAX_, HIGHT_MAX_),
		DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, (int)black_alpha_)
	);
	
	DX9::SpriteBatch->DrawSimple(
		white_.Get(),
		SimpleMath::Vector3(0.0f, 0.0f, SPRITE_POS_Z_),
		RectWH(0, 0, WIDTH_MAX_, HIGHT_MAX_),
		DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, (int)white_alpha_)
	);
}