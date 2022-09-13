#include "Classes/Player/PlayerAttack.h"
#include "Classes/Player/Player.h"

void PlayerAttack::Initialize(){
	attack_flg_ = false;
	attack_time_ = 0.0f;
}

void PlayerAttack::Update(const float deltaTime, Player* const player){
    attack_time_ = std::min(attack_time_ + deltaTime, MAX_ATTACK_TIME_);
    attack_flg_  = true;
    if (attack_time_ >= MAX_ATTACK_TIME_) {
        attack_flg_ = false;
        player->SwitchState(PLAYER_STATE::WAIT);
    }
}