#include "Classes/Player/Action/PlayerAttack.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"


/**
* @brief �l�̏�����
*/
void player::PlayerAttack::Initialize(){
	attack_flg_ = false;
	attack_time_ = 0.0f;
}

/**
* @brief �U���̍X�V
* 
* @param[in] deltaTime ����
* @param[out] player �v���C���[
*/
void player::PlayerAttack::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m){
    attack_time_ = std::min(attack_time_ + deltaTime, MAX_ATTACK_TIME_);
    attack_flg_  = true;
    if (attack_time_ >= MAX_ATTACK_TIME_) {
        attack_flg_ = false;
        act_m->SwitchState(PLAYER_STATE::WAIT, player);
    }
}