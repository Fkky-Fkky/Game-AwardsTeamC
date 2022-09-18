#include "Classes/Player/Player.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Collision/ObjectManager.h"

void Player::Initialize() {
    player_motion_track_ = 0;

	pos_ = SimpleMath::Vector3::Zero;
	rot_ = SimpleMath::Vector3(0.0f, RIGHT_WARD_,0.0f);

    jump_motion_time_ = 0.0f;
    death_motion_time_ = 0.0f;
    is_jump_motion_play_ = false;
    is_switch_state_death_ = false;

    player_status_.Initialize();
    player_action_state_ = PLAYER_STATE::WAIT;
    player_state_ = &player_wait_;
    player_state_->Initialize();
    player_attack_colision_.Initialize();
}

void Player::LoadAssets() {
    model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player/warrior/warrior.x");
    model_->SetScale(PLAYER_SCALE_);

    player_colision_.LoadAssets(model_.get());
    player_attack_colision_.LoadAssets(model_.get());

    DX12Effect.Create(L"Effect/upper_attack/upper_attack.efk", "swaord");
    DX12Effect.Create(L"Effect/Eff_Jump_001/Eff_jump_001.efk", "jump");
    DX12Effect.Create(L"Effect/Eff_kaihi/Eff_kaihi.efk", "avoid");

    avoid_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Avoidance.wav");
    jump_se_  = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Jump.wav");

    for (int i = 0; i < MOTION_MAX_; ++i) {
        model_->SetTrackEnable(i, false);
    }
    model_->SetTrackEnable(player_motion_track_, true);
}

void Player::Update(const float deltaTime, const ObjectManager* const obj_m) { 
    player_status_.Update(deltaTime, obj_m);

    if (obj_m->GetPlayerDmgFlag() && !IsPlayerInvincible()) {
        SwitchState(PLAYER_STATE::DAMAGE);
    }
    if (GetPlayerHP() <= 0.0f && !is_switch_state_death_) {
        SwitchState(PLAYER_STATE::DEATH);
    }

    player_state_->Update(deltaTime, this);

    if (is_jump_motion_play_) {
        JumpMotion(deltaTime);
    }
    model_->AdvanceTime(deltaTime);
    player_attack_colision_.Update(deltaTime, model_.get(), this);
    player_colision_.Update(deltaTime, model_.get());
}

void Player::Render() const { 
    model_->SetPosition(pos_);
    model_->SetRotation(
        XMConvertToRadians(rot_.x),
        XMConvertToRadians(rot_.y),
        XMConvertToRadians(rot_.z)
    );
	model_->Draw();

    player_colision_.Render();
    player_attack_colision_.Render();
}

void Player::SetMotion(const PLAYER_MOTION player_motion) {   //モーションの再生処理
    player_motion_track_ = (int)player_motion;

    ResetPlayerMotion();

    if (player_motion_track_ == (int)PLAYER_MOTION::JUMP &&
        !is_jump_motion_play_) {
        is_jump_motion_play_ = true;
    }
    else {
        is_jump_motion_play_ = false;
        jump_motion_time_ = 0.0f;
    }
    model_->SetTrackEnable(player_motion_track_, true);
}

void Player::ResetPlayerMotion() const {  //モーションのトラックをリセット
    for (int i = 0; i < MOTION_MAX_; ++i) {
        if (player_motion_track_ == i) {
            continue;
        }
        model_->SetTrackEnable(i, false);
        model_->SetTrackPosition(i, 0.0f);
    }
}

void Player::JumpMotion(const float deltaTime) {    //ジャンプモーション処理
    const float JUMP_UP_TIME_MAX_ = 0.36f;
    jump_motion_time_ = std::min(jump_motion_time_ + deltaTime, JUMP_UP_TIME_MAX_);
    if (jump_motion_time_ >= JUMP_UP_TIME_MAX_) {
        model_->SetTrackEnable((int)PLAYER_MOTION::JUMP, false);
    }
}

void Player::DeathMotion(const float delaTime) {    //デスモーション処理
    const float DEATH_MOTION_TIME_MAX_ = 0.86f;
    death_motion_time_ = std::min(death_motion_time_ + delaTime, DEATH_MOTION_TIME_MAX_);
    if (death_motion_time_ >= DEATH_MOTION_TIME_MAX_) {
        model_->SetTrackEnable(player_motion_track_, false);
    }
}

PLAYER_MOTION Player::ConvertToMotion(const PLAYER_STATE player_state) const {  //プレイヤーの状態をモーショントラックに変換
    PLAYER_MOTION motion_track_;
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

void Player::SwitchState(const PLAYER_STATE state) {
    if (player_action_state_ == PLAYER_STATE::ATTACK) {
        player_state_->Initialize();
    }
    player_action_state_ = state;
    
    switch (player_action_state_) {
    case PLAYER_STATE::WAIT:        player_state_ = &player_wait_;          break;
    case PLAYER_STATE::RIGHT_MOVE:  player_state_ = &player_right_move_;    break;
    case PLAYER_STATE::LEFT_MOVE :  player_state_ = &player_left_move_;     break;
    case PLAYER_STATE::JUMP:        player_state_ = &player_jump_;          break;
    case PLAYER_STATE::ATTACK:      player_state_ = &player_attack_;        break;
    case PLAYER_STATE::DAMAGE:      player_state_ = &player_dmg_;           break;
    case PLAYER_STATE::DEATH:       player_state_ = &player_death_;         break;
    }
    SetMotion(ConvertToMotion(player_action_state_));
    player_state_->Initialize();
}

void Player::PlayAvoidSE() const {
    avoid_se_->Play();
}

void Player::PlayJumpSE() const {
    jump_se_->Play();
}