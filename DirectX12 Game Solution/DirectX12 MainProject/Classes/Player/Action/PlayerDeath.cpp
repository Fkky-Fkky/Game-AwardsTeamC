#include "Classes/Player/Action/PlayerDeath.h"
#include "Classes/Player/Player.h"

/**
* @brief �l�̏�����
*/
void player::PlayerDeath::Initialize() {
	is_player_death_ = true;
}

/**
* @brief ���S��Ԃ̍X�V
*
* @param[in] deltaTime ����
* @param[out] player �v���C���[
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