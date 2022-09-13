#include "Classes/UI/UI.h"
#include "Classes/Collision/ObjectManager.h"

void UI::Initialize() {
	player_side_shake_	   = RIGHT;
	player_vertical_shake_ = UP;
	boss_side_shake_	 = RIGHT;
	boss_vertical_shake_ = UP;

	player_hp_width_ = PLAYER_HP_MAX_WIDTH_;
	boss_hp_width_	 = BOSS_HP_MAX_WIDTH_;
	old_player_hp_ = 0.0f;
	old_boss_hp_   = 0.0f;
	time_delta_	   = 0.0f;
	player_shake_time_ = 0.0f;
	is_player_damage_ = false;
	is_boss_damage_	  = false;

	player_hp_pos_ = SimpleMath::Vector3(PLAYER_HP_POS_X_, PLAYER_HP_POS_Y_, 0.0f);
	boss_hp_pos_   = SimpleMath::Vector3(BOSS_HP_POS_X_,   BOSS_HP_POS_Y_,	 0.0f);
}

void UI::LoadAssets() {
	player_hp_top_	  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_max.png");
	player_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_min.png");
	boss_hp_top_	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_max.png");
	boss_hp_bottom_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_min.png");
}

void UI::Update(const float deltaTime, const ObjectManager* const obj_m) {
	time_delta_ = deltaTime;
	player_hp_width_ = obj_m->GetPlayerHP() * PLAYER_HP_WIDTH_DIVIDE_;
	boss_hp_width_	 = obj_m->GetBossHP()	* BOSS_HP_WIDTH_DIVIDE_;

	if (old_player_hp_ > player_hp_width_) {
		is_player_damage_ = true;
	}
	if (is_player_damage_) {
		PlayerUIShake();
	}

	if (old_boss_hp_ > boss_hp_width_) {
		is_boss_damage_ = true;
	}
	if (is_boss_damage_) {
		BossUIShake();
	}

	old_player_hp_ = player_hp_width_;
	old_boss_hp_   = boss_hp_width_;
}

void UI::Render() const{
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

void UI::PlayerUIShake() {	//プレイヤーのHPを揺らす
	const float SHAKE_TIME_MAX_  = 0.5f;
	const float SHAKE_POS_MIN_X_ = 40.0f;
	const float SHAKE_POS_MAX_X_ = 60.0f;
	const float SHAKE_POS_MIN_Y_ = 670.0f;
	const float SHAKE_POS_MAX_Y_ = 690.0f;
	const float SHAKE_POWER_X_ = 300.0f;
	const float SHAKE_POWER_Y_ = 200.0f;
	
	player_shake_time_ = std::min(player_shake_time_ + time_delta_, SHAKE_TIME_MAX_);

	if (player_side_shake_ == LEFT) {
		player_hp_pos_.x = std::max(player_hp_pos_.x - SHAKE_POWER_X_ * time_delta_, SHAKE_POS_MIN_X_);
		if (player_hp_pos_.x <= SHAKE_POS_MIN_X_) {
			player_side_shake_ = RIGHT;
		}
	}
	else {
		player_hp_pos_.x = std::min(player_hp_pos_.x + SHAKE_POWER_X_ * time_delta_, SHAKE_POS_MAX_X_);
		if (player_hp_pos_.x >= SHAKE_POS_MAX_X_) {
			player_side_shake_ = LEFT;
		}
	}

	if (player_vertical_shake_ == UP) {
		player_hp_pos_.y = std::max(player_hp_pos_.y - SHAKE_POWER_Y_ * time_delta_, SHAKE_POS_MIN_Y_);
		if (player_hp_pos_.y <= SHAKE_POS_MIN_Y_) {
			player_vertical_shake_ = DOWN;
		}
	}
	else {
		player_hp_pos_.y = std::min(player_hp_pos_.y + SHAKE_POWER_Y_ * time_delta_, SHAKE_POS_MAX_Y_);
		if (player_hp_pos_.y >= SHAKE_POS_MAX_Y_) {
			player_vertical_shake_ = UP;
		}
	}

	if (player_shake_time_ >= SHAKE_TIME_MAX_) {
		player_shake_time_ = 0.0f;
		player_hp_pos_.x = PLAYER_HP_POS_X_;
		player_hp_pos_.y = PLAYER_HP_POS_Y_;
		is_player_damage_ = false;
	}
}

void UI::BossUIShake() {	//ボスのHPを揺らす
	const float SHAKE_TIME_MAX_ = 0.4f;
	const float SHAKE_POS_MIN_X_ = 170.0f;
	const float SHAKE_POS_MAX_X_ = 210.0f;
	const float SHAKE_POS_MIN_Y_ = 10.0f;
	const float SHAKE_POS_MAX_Y_ = 50.0f;
	const float SHAKE_POWER_X_ = 500.0f;
	const float SHAKE_POWER_Y_ = 500.0f;
	boss_shake_time_ = std::min(boss_shake_time_ + time_delta_, SHAKE_TIME_MAX_);

	if (boss_vertical_shake_ == UP) {
		boss_hp_pos_.y = std::max(boss_hp_pos_.y - SHAKE_POWER_Y_ * time_delta_, SHAKE_POS_MIN_Y_);
		if (boss_hp_pos_.y <= SHAKE_POS_MIN_Y_) {
			boss_vertical_shake_ = DOWN;
		}
	}
	else {
		boss_hp_pos_.y = std::min(boss_hp_pos_.y + SHAKE_POWER_Y_ * time_delta_, SHAKE_POS_MAX_Y_);
		if (boss_hp_pos_.y >= SHAKE_POS_MAX_Y_) {
			boss_vertical_shake_ = UP;
		}
	}
	if (boss_side_shake_ == RIGHT) {
		boss_hp_pos_.x = std::min(boss_hp_pos_.x + SHAKE_POWER_X_ * time_delta_, SHAKE_POS_MAX_X_);
		if (boss_hp_pos_.x >= SHAKE_POS_MAX_X_) {
			boss_side_shake_ = LEFT;
		}
	}
	else {
		boss_hp_pos_.x = std::max(boss_hp_pos_.x - SHAKE_POWER_X_ * time_delta_, SHAKE_POS_MIN_X_);
		if (boss_hp_pos_.x <= SHAKE_POS_MIN_X_) {
			boss_side_shake_ = RIGHT;
		}
	}

	if (boss_shake_time_ >= SHAKE_TIME_MAX_) {
		boss_shake_time_ = 0.0f;
		boss_hp_pos_.x = BOSS_HP_POS_X_;
		boss_hp_pos_.y = BOSS_HP_POS_Y_;
		is_boss_damage_ = false;
	}
}