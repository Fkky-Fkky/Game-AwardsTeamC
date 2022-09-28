#include "Classes/Player/PlayerStatus.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 値の初期化
*/
void player::PlayerStatus::Initialize() {
	hp_ = PLAYER_HP_MAX_;
	invincible_time_ = 0.0f;
	damage_ = 0.0f;
	is_invincible_ = false;
}

/**
* @brief HPの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void player::PlayerStatus::Update(const float deltatime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltatime, 0.0f);
	if (invincible_time_ <= 0.0f) {
		is_invincible_ = false;
	}

	if (obj_m->IsPlayerDmg() && !is_invincible_) {
		is_invincible_ = true;
		if (obj_m->IsBossHandOpen()) {
			damage_ = OPEN_DAMAGE_;
		}
		else {
			damage_ = CLOSE_DAMAGE_;
		}
		DamageProcess();
	}
}

/**
* @brief プレイヤーのダメージ処理
*/
void player::PlayerStatus::DamageProcess() {
	hp_ -= damage_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}