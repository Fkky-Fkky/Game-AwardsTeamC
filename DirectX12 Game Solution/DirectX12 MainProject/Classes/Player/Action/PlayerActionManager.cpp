#include "Classes/Player/Action/PlayerActionManager.h"
#include "Classes/Object/ObjectManager.h"
#include "Classes/Player/Player.h"

/**
* @brief 値の初期化
*/
void PlayerActionManager::Initialize() {
    is_switch_state_death_ = false;
    player_action_state_ = PLAYER_STATE::WAIT;
    action_ = &wait_;
    action_->Initialize();
}

/**
* @brief プレイヤーアクションの更新
* 
* @param[in] deltaTime 時間
* @param[out] player プレイヤー
* @param[in] obj_m オブジェクトマネージャー
*/
void PlayerActionManager::Update(const float deltaTime, Player* const player, const ObjectManager* const obj_m) {
    if (player->GetPlayerHP() <= 0.0f) {
        if (!is_switch_state_death_) {
            SwitchState(PLAYER_STATE::DEATH, player);
            is_switch_state_death_ = true;
        }
    }
    else {
        if (obj_m->IsPlayerDmg() && !IsPlayerInvincible()) {
            SwitchState(PLAYER_STATE::DAMAGE, player);
        }
    }

    action_->Update(deltaTime, player, this);
}

/**
* @brief 状態変更
*
* @param[in] state 変更する状態
* @param[out] player プレイヤー
*/
void PlayerActionManager::SwitchState(const PLAYER_STATE state, Player* const player) {
    if (player_action_state_ == PLAYER_STATE::ATTACK) {
        action_->Initialize();
    }
    player_action_state_ = state;

    switch (player_action_state_) {
    case PLAYER_STATE::WAIT:        action_ = &wait_;          break;
    case PLAYER_STATE::RIGHT_MOVE:  action_ = &right_move_;    break;
    case PLAYER_STATE::LEFT_MOVE:   action_ = &left_move_;     break;
    case PLAYER_STATE::JUMP:        action_ = &jump_;          break;
    case PLAYER_STATE::ATTACK:      action_ = &attack_;        break;
    case PLAYER_STATE::DAMAGE:      action_ = &dmg_;           break;
    case PLAYER_STATE::DEATH:       action_ = &death_;         break;
    }
    player->SetMotion(ConvertToMotion(player_action_state_));
    action_->Initialize();
}

/**
* @brief プレイヤーの状態をモーショントラックに変換
*
* @param[in] player_state プレイヤーの状態
* @return モーションのトラック
*/
int PlayerActionManager::ConvertToMotion(const PLAYER_STATE player_state) const {
    int motion_track_;
    switch (player_state) {
    case    PLAYER_STATE::WAIT:         motion_track_ = PLAYER_MOTION::WAIT;    break;
    case    PLAYER_STATE::RIGHT_MOVE:
    case    PLAYER_STATE::LEFT_MOVE:    motion_track_ = PLAYER_MOTION::MOVE;    break;
    case    PLAYER_STATE::JUMP:         motion_track_ = PLAYER_MOTION::JUMP;    break;
    case    PLAYER_STATE::ATTACK:       motion_track_ = PLAYER_MOTION::ATTACK;  break;
    case    PLAYER_STATE::DAMAGE:       motion_track_ = PLAYER_MOTION::DAMAGE;  break;
    case    PLAYER_STATE::DEATH:        motion_track_ = PLAYER_MOTION::DEATH;   break;
    default:                            motion_track_ = PLAYER_MOTION::WAIT;    break;
    }

    return motion_track_;
}