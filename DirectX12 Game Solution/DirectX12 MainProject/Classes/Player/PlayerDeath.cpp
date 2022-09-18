#include "Classes/Player/PlayerDeath.h"
#include "Classes/Player/Player.h"

void player::PlayerDeath::Initialize() {
	is_player_death_ = true;
}

void player::PlayerDeath::Update(const float deltaTime, Player* const player) {
	SimpleMath::Vector3 pos_ = player->GetPlayerPosition();
	if (pos_.y >= 0.0f) {
		pos_.y  = std::max(pos_.y - FALL_SPEED_ * deltaTime, 0.0f);
	}
	player->SetPlayerPosition(pos_);
}