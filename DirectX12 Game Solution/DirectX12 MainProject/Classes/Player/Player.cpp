#include "Classes/Player/Player.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 値の初期化
*/
void Player::Initialize() {
    player_motion_track_ = 0;
    jump_motion_time_  = 0.0f;
    death_motion_time_ = 0.0f;
    is_jump_motion_play_   = false;
    is_death_motion_play_  = false;;
    pos_ = SimpleMath::Vector3::Zero;
    rot_ = SimpleMath::Vector3(0.0f, RIGHT_WARD_, 0.0f);
    atk_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/SE/PlayerAtk.wav");

    status_.Initialize();
    attack_colision_.Initialize();
    action_.Initialize();
}

/**
* @brief モデル、エフェクトの読み込み
*/
void Player::LoadAssets() {
    model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player/warrior/warrior.x");
    model_->SetScale(PLAYER_SCALE_);

    colision_.LoadAssets(model_.get());
    attack_colision_.LoadAssets(model_.get());

    for (int i = 0; i < MOTION_MAX_; ++i) {
        model_->SetTrackEnable(i, false);
    }
    model_->SetTrackEnable(player_motion_track_, true);

    DX12Effect.Create(L"Effect/upper_attack/upper_attack.efk", "swaord");
}

/**
* @brief プレイヤーの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void Player::Update(const float deltaTime, const ObjectManager* const obj_m) {
    status_.Update(deltaTime, obj_m);
    action_.Update(deltaTime, this, obj_m);

    if (is_jump_motion_play_) {
        JumpMotion(deltaTime);
    }
    if (is_death_motion_play_) {
        DeathMotion(deltaTime);
    }

    model_->AdvanceTime(deltaTime);
    attack_colision_.Update(deltaTime, model_.get(), this);
    colision_.Update(model_.get());
}

/**
* @brief モデルの描画
*/
void Player::Render() const {
    model_->SetPosition(pos_);
    model_->SetRotation(
        XMConvertToRadians(rot_.x),
        XMConvertToRadians(rot_.y),
        XMConvertToRadians(rot_.z)
    );
    model_->Draw();
}

/**
* @brief プレイヤーモーションの再生処理
* 
* @param[in] player_motion 再生するモーション
*/
void Player::SetMotion(const int player_motion) {
    player_motion_track_ = player_motion;

    ResetPlayerMotion();

    if (player_motion_track_ == (int)PLAYER_MOTION::JUMP &&
        !is_jump_motion_play_) {
        is_jump_motion_play_ = true;
    }
    else {
        is_jump_motion_play_ = false;
        jump_motion_time_ = 0.0f;
    }

    if (player_motion_track_ == (int)PLAYER_MOTION::DEATH) {
        is_death_motion_play_ = true;
    }
    model_->SetTrackEnable(player_motion_track_, true);
}

/**
* @brief モーションのトラックをリセット
*/
void Player::ResetPlayerMotion() const {
    for (int i = 0; i < MOTION_MAX_; ++i) {
        if (player_motion_track_ == i) {
            continue;
        }
        model_->SetTrackEnable(i, false);
        model_->SetTrackPosition(i, 0.0f);
    }
}

/**
* @brief ジャンプモーション処理
* 
* @param[in] deltaTIme 時間
*/
void Player::JumpMotion(const float deltaTime) {
    const float JUMP_UP_TIME_MAX_ = 0.36f;
    jump_motion_time_ = std::min(jump_motion_time_ + deltaTime, JUMP_UP_TIME_MAX_);
    if (jump_motion_time_ >= JUMP_UP_TIME_MAX_) {
        model_->SetTrackEnable((int)PLAYER_MOTION::JUMP, false);
    }
}

/**
* @brief デスモーション処理
* 
* @param[deltaTime] 時間
*/
void Player::DeathMotion(const float delaTime) {
    const float DEATH_MOTION_TIME_MAX_ = 0.86f;
    death_motion_time_ = std::min(death_motion_time_ + delaTime, DEATH_MOTION_TIME_MAX_);
    if (death_motion_time_ >= DEATH_MOTION_TIME_MAX_) {
        model_->SetTrackEnable(player_motion_track_, false);
    }
}

/**
* @brief 攻撃SE再生
*/
void Player::PlayAtkSE() const {
    atk_se_->Play();
}