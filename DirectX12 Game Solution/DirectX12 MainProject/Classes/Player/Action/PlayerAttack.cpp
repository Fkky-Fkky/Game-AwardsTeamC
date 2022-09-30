#include "Classes/Player/Action/PlayerAttack.h"
#include "Classes/Player/Player.h"
#include "Classes/Player/Action/PlayerActionManager.h"


/**
* @brief 値の初期化
*/
void player::PlayerAttack::Initialize(){
	attack_flg_ = false;
	attack_time_ = 0.0f;
}

/**
* @brief 攻撃の更新
* 
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
*/
void player::PlayerAttack::Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m){
    attack_time_ = std::min(attack_time_ + deltaTime, MAX_ATTACK_TIME_);
    attack_flg_  = true;
    if (attack_time_ >= MAX_ATTACK_TIME_) {
        attack_flg_ = false;
        act_m->SwitchState(PLAYER_STATE::WAIT, player);
    }
}