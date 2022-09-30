#include "Classes/Player/Action/PlayerDeath.h"
#include "Classes/Player/Player.h"

/**
* @brief 値の初期化
*/
void player::PlayerDeath::Initialize() {
	is_player_death_ = true;
}

/**
* @brief 死亡状態の更新
*
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
*/
void player::PlayerDeath::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) {
	SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
	if (pos_.y >= DEATH_POS_Y_) {
		pos_.y = std::max(pos_.y - FALL_SPEED_ * deltaTime, DEATH_POS_Y_);
	}
	else {
		pos_.y = DEATH_POS_Y_;
	}
	player->SetPlayerPosition(pos_);
}