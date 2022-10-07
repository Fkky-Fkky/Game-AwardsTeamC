#include "Classes/UI/UI.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 値の初期化
*/
void UI::Initialize() {
	time_delta_ = 0.0f;
	ReadFile();

	for (int i = 0; i < CHARACTER_MAX_; i++) {
		side_shake_state_[i]	 = RIGHT;
		vertical_shake_state_[i] = UP;
		hp_width_[i] = 0.0f;
		old_hp_[i]	 = 0.0f;
		ui_shake_time_[i] = 0.0f;
		is_damage_[i] = false;
		hp_pos_[i] = SimpleMath::Vector3(hp_init_pos_x_[i], hp_init_pos_y_[i], 0.0f);
	}	
}

/**
* @brief 画像の読み込み
*/
void UI::LoadAssets() {
	hp_top_[PLAYER] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_max.png");
	hp_top_[BOSS]	= DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_max.png");
	hp_bottom_[PLAYER] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/player_min.png");
	hp_bottom_[BOSS]   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"UI/boss_min.png");
}

/**
* @brief UIの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void UI::Update(const float deltaTime, const ObjectManager* const obj_m) {
	time_delta_ = deltaTime;
	float hp_[CHARACTER_MAX_]{};
	hp_[PLAYER] = obj_m->GetPlayerHP() * PLAYER_HP_WIDTH_DIVIDE_;
	hp_[BOSS]	= obj_m->GetBossHP()   * BOSS_HP_WIDTH_DIVIDE_;

	for (int i = 0; i < CHARACTER_MAX_; i++) {
		if (hp_width_[i] > hp_[i]) {
			hp_width_[i] = std::max(hp_width_[i] - HP_SPEED_ * deltaTime, hp_[i]);
		}
		else {
			hp_width_[i] = std::min(hp_width_[i] + HP_SPEED_ * deltaTime, hp_[i]);
		}

		if (old_hp_[i] > hp_[i]) {
			is_damage_[i] = true;
		}

		if (is_damage_[i]) {
			UIShake(i);
		}

		old_hp_[i] = hp_[i];
	}
}

/**
* @brief UIの描画
*/
void UI::Render() const{
	for (int i = 0; i < CHARACTER_MAX_; i++) {
		DX9::SpriteBatch->DrawSimple(
			hp_bottom_[i].Get(),
			hp_pos_[i]
		);

		DX9::SpriteBatch->DrawSimple(
			hp_top_[i].Get(),
			hp_pos_[i],
			RectWH(0, 0, (int)hp_width_[i], HP_HIGHT_)
		);
	}
}

/**
* @brief HPを揺らす
* 
* @param[in] i 動かす添え字
*/
void UI::UIShake(const int i) {
	ui_shake_time_[i] = std::min(ui_shake_time_[i] + time_delta_, ui_shake_time_max_[i]);

	if (side_shake_state_[i] == LEFT) {
		hp_pos_[i].x = std::max(hp_pos_[i].x - ui_side_shake_power_[i] * time_delta_, ui_side_shake_pos_min_[i]);
		if (hp_pos_[i].x <= ui_side_shake_pos_min_[i]) {
			side_shake_state_[i] = RIGHT;
		}
	}
	else {
		hp_pos_[i].x = std::min(hp_pos_[i].x + ui_side_shake_power_[i] * time_delta_, ui_side_shake_pos_max_[i]);
		if (hp_pos_[i].x >= ui_side_shake_pos_max_[i]) {
			side_shake_state_[i] = LEFT;
		}
	}

	if (vertical_shake_state_[i] == UP) {
		hp_pos_[i].y = std::max(hp_pos_[i].y - ui_vertical_shake_power_[i] * time_delta_, ui_vertical_shake_pos_min_[i]);
		if (hp_pos_[i].y <= ui_vertical_shake_pos_min_[i]) {
			vertical_shake_state_[i] = DOWN;
		}
	}
	else {
		hp_pos_[i].y = std::min(hp_pos_[i].y + ui_vertical_shake_power_[i] * time_delta_, ui_vertical_shake_pos_max_[i]);
		if (hp_pos_[i].y >= ui_vertical_shake_pos_max_[i]) {
			vertical_shake_state_[i] = UP;
		}
	}

	if (ui_shake_time_[i] >= ui_shake_time_max_[i]) {
		ui_shake_time_[i] = 0.0f;
		hp_pos_[i].x = hp_init_pos_x_[i];
		hp_pos_[i].y = hp_init_pos_y_[i];
		is_damage_[i] = false;
	}
}

/**
* @brief CSVファイルを読み込み、パラメーターを設定
*/
void UI::ReadFile() {
	FILE* fp;
	if (fopen_s(&fp, "CSV/UI_data.csv", "r") != 0) {
		assert(!"UI_data.csvを開けません");
		throw std::exception();
	}

	char file_data_[256];
	fgets(file_data_, 255, fp);

	for (int i = 0; i < CHARACTER_MAX_; i++) {
		float shake_range_x_;
		float shake_range_y_;
		fscanf_s(
			fp,
			"%f,%f,%f,%f,%f,%f,%f,",
			&hp_init_pos_x_[i], &hp_init_pos_y_[i], &shake_range_x_, &shake_range_y_,
			&ui_side_shake_power_[i], &ui_vertical_shake_power_[i], &ui_shake_time_max_[i]
		);
		ui_side_shake_pos_min_[i] = hp_init_pos_x_[i] - shake_range_x_;
		ui_side_shake_pos_max_[i] = hp_init_pos_x_[i] + shake_range_x_;
		ui_vertical_shake_pos_min_[i] = hp_init_pos_y_[i] - shake_range_y_;
		ui_vertical_shake_pos_max_[i] = hp_init_pos_y_[i] + shake_range_y_;
	}
	fclose(fp);
}