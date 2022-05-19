#include "Classes/Player/Player.h"
#include "Base/DX12Effekseer.h"

void Player::Initialize() {
	pos_ = SimpleMath::Vector3::Zero;
	rot_ = SimpleMath::Vector3::Zero;

    SwitchState(PLAYER_STATE::WAIT);
    player_hp_ = 30.0f;
    hit_flag_ = false;
}

void Player::LoadAssets() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Player/chara_mock.x");
    model_->SetScale(1.0f);

    player_colision_.LoadAssets(model_.get());
    player_attack_colision_.LoadAssets(model_.get());

    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

    DX12Effect.Create(L"Effect/Eff_Sword_001/Eff_Sword_001.efk", "swaord");
    DX12Effect.Create(L"Effect/Eff_Jump_001/Eff_jump_001.efk", "jump");
}

void Player::Update(const float deltaTime) {
    player_state_->Update(deltaTime, *this);

    player_colision_.Update(deltaTime, model_.get());
    player_attack_colision_.Update(deltaTime, model_.get());
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
        L"ÉvÉåÉCÉÑÅ[:%f", player_hp_
    );
}

void Player::HitPlayer(bool player_hit_flag) {
    if (player_hit_flag) {
        if(!hit_flag_)
            HitProcessing();
    }
    else {
        hit_flag_ = false;
    }
}

void Player::HitProcessing() {
    player_hp_ -= 1.0f;
    hit_flag_ = true;
}

void Player::SwitchState(PLAYER_STATE state) {
    switch (state) {
    case PLAYER_STATE::WAIT:        player_state_ = &player_wait_;          break;
    case PLAYER_STATE::RIGHT_MOVE:  player_state_ = &player_right_move_;    break;
    case PLAYER_STATE::LEFT_MOVE :  player_state_ = &player_left_move_;     break;
    case PLAYER_STATE::JUMP:        player_state_ = &player_jump_;          break;
    case PLAYER_STATE::AVOID:       player_state_ = &player_avoid_;         break;
    }
}