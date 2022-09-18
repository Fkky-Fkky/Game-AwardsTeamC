#include "Classes/Player/PlayerDeath.h"
#include "Classes/Player/Player.h"

void player::PlayerDeath::Initialize() {
	is_player_death_ = true;
}

void player::PlayerDeath::Update(const float deltaTime, Player* const player) {
	SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
	if (pos_.y >= DEATH_POS_Y_) {
		pos_.y = std::max(pos_.y - FALL_SPEED_ * deltaTime, DEATH_POS_Y_);
	}
	else {
		pos_.y = DEATH_POS_Y_;
	}
	player->SetPlayerPosition(pos_);
}