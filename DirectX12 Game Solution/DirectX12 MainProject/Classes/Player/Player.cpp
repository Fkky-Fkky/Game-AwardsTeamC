#include "Classes/Player/Player.h"
#include "Base/DX12Effekseer.h"
#include "Classes/Collision/ObjectManager.h"

void Player::Initialize() {
    initialize_stop_flag_ = false;

	pos_ = SimpleMath::Vector3::Zero;
	rot_ = SimpleMath::Vector3(0.0f, RIGHT_WARD_,0.0f);

    player_state_ = &player_wait_;
    player_state_->Initialize();
    player_attack_colision_.Initialize();
}

void Player::LoadAssets() {
    model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Player/warrior/warrior.x");
    model_->SetScale(0.02f);

    player_colision_.LoadAssets(model_.get());
    player_attack_colision_.LoadAssets(model_.get());

    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

    DX12Effect.Create(L"Effect/upper_attack/upper_attack.efk", "swaord");
    DX12Effect.Create(L"Effect/Eff_Jump_001/Eff_jump_001.efk", "jump");
    DX12Effect.Create(L"Effect/Eff_kaihi/Eff_kaihi.efk", "avoid");

    avoid_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Avoidance.wav");
    jump_se_  = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Jump.wav");

    for (int i = 0; i < MOTION_MAX_; ++i) {
        model_->SetTrackEnable(i, false);
    }
    model_->SetTrackEnable((int)PLAYER_MOTION::WAIT, true);
}

void Player::Update(const float deltaTime, ObjectManager* obj_m) {
    
    if (obj_m->GetPlayerDmgFlag()) {
        SwitchState(PLAYER_STATE::DAMAGE);
    }

    player_state_->Update(deltaTime, *this);

    player_attack_colision_.Update(deltaTime, model_.get(), this);

    model_->AdvanceTime(deltaTime);
    if (is_jump_motion_play_) {
        const float JUMP_TIME_MAX_ = 1.0f;
        jump_motion_time_ = std::min(jump_motion_time_ + deltaTime, JUMP_TIME_MAX_);
        if (jump_motion_time_ >= JUMP_TIME_MAX_) {
            model_->SetTrackEnable((int)PLAYER_MOTION::JUMP, false);
        }
    }

    player_colision_.Update(deltaTime, model_.get());
}

void Player::Render() {
    
    model_->SetPosition(pos_);
    model_->SetRotation(rot_);
	model_->Draw();

    player_colision_.Render();

    player_attack_colision_.Render();
}

void Player::Render2D() {
    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 30.0f),
        DX9::Colors::Red,
        L"�v���C���[:%f", player_dmg_.GetPlayerHP()
    );
}

void Player::SetMotion(PLAYER_MOTION player_motion) {
    PLAYER_MOTION motion_track_ = player_motion;

    ResetPlayerMotion();

    if (motion_track_ == PLAYER_MOTION::JUMP) {
        is_jump_motion_play_ = true;
    }
    else {
        is_jump_motion_play_ = false;
        jump_motion_time_ = 0.0f;
    }
    model_->SetTrackEnable((int)motion_track_, true);
}

void Player::PlayAvoidSE() {
    avoid_se_->Play();
}

void Player::PlayJumpSE() {
    jump_se_->Play();
}

void Player::ResetPlayerMotion() {
    for (int i = 0; i < MOTION_MAX_; ++i) {
        model_->SetTrackEnable(i, false);
        model_->SetTrackPosition(i, 0.0f);
    }
}

PLAYER_MOTION Player::ConvertToMotion(PLAYER_STATE player_state) {  //�v���C���[�̏�Ԃ����[�V�����g���b�N�ɕϊ�
    PLAYER_MOTION motion_track_;
    switch (player_state) {
    case    PLAYER_STATE::WAIT:         motion_track_ = PLAYER_MOTION::WAIT;    break;
    case    PLAYER_STATE::RIGHT_MOVE:
    case    PLAYER_STATE::LEFT_MOVE:    motion_track_ = PLAYER_MOTION::MOVE;    break;
    case    PLAYER_STATE::JUMP:         motion_track_ = PLAYER_MOTION::JUMP;    break;
    default:                            motion_track_ = PLAYER_MOTION::WAIT;    break;
    }

    return motion_track_;
}

void Player::SwitchState(PLAYER_STATE state) {
    player_action_state_ = state;
    switch (player_action_state_) {
    case PLAYER_STATE::WAIT:        player_state_ = &player_wait_;          break;
    case PLAYER_STATE::RIGHT_MOVE:  player_state_ = &player_right_move_;    break;
    case PLAYER_STATE::LEFT_MOVE :  player_state_ = &player_left_move_;     break;
    case PLAYER_STATE::JUMP:        player_state_ = &player_jump_;          break;
    case PLAYER_STATE::AVOID:       player_state_ = &player_avoid_;         break;
    case PLAYER_STATE::DAMAGE:      player_state_ = &player_dmg_;           break;
    }
    SetMotion(ConvertToMotion(player_action_state_));
    if (!initialize_stop_flag_) {
        player_state_->Initialize();
    }
}