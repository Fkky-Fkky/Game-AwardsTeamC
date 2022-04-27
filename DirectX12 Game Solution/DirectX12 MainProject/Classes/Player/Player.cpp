#include "Classes/Player/Player.h"

void Player::Initialize() {
	pos_ = SimpleMath::Vector3::Zero;
	rot_ = SimpleMath::Vector3::Zero;

    attack_x_ = 0.0f;
    attack_flg_ = false;
    attack_time_ = 0.0f;

    player_hp_ = 30.0f;
    hit_flag_ = false;
}

void Player::LoadAssets() {
	model_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Player/chara_mock.x");
    font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);

    player_colision_.LoadAssets(model_.get());

    player_attack_collision_ = model_->GetBoundingOrientedBox();
    player_attack_collision_.Extents = SimpleMath::Vector3(player_attack_collision_.Extents) * 1.0f;

    player_attack_collision_model_ = DX9::Model::CreateBox(
        DXTK->Device9,
        player_attack_collision_.Extents.x,
        player_attack_collision_.Extents.y,
        player_attack_collision_.Extents.z
    );

    D3DMATERIAL9 material_attack_{};
    material_attack_.Diffuse = DX9::Colors::Value(0.0f, 0.0f, 1.0f, 0.75f);
    player_attack_collision_model_->SetMaterial(material_attack_);

    model_->SetScale(1.0f);
}

void Player::Update(const float deltaTime) {

    player_move_.Update(deltaTime, pos_, rot_);
    player_jump_.Update(deltaTime, pos_);

    float player_y_angle_ = DirectX::XMConvertToDegrees(rot_.y);

    if (player_y_angle_ < 0) {
        attack_x_ = 1.5f;
    }

    if (player_y_angle_ > 0) {
        attack_x_ = -1.5f;
    }

    if (!attack_flg_ && DXTK->KeyEvent->pressed.Space) {
        attack_flg_ = true;
    }

    if (attack_flg_) {
        attack_time_ += 1.0f * deltaTime;
        if (attack_time_ > 0.3f) {
            attack_flg_ = false;
            attack_time_ = 0.0f;
        }
    }

    player_colision_.Update(deltaTime, model_.get());

    player_attack_collision_.Center = model_->GetPosition() + SimpleMath::Vector3(attack_x_,1.5f,0);
    player_attack_collision_.Orientation = model_->GetRotationQuaternion();

    /*collision.PlayerCollision(player_collision_);*/
}

void Player::Render() {
    
    model_->SetPosition(pos_);
    model_->SetRotation(rot_);
	model_->Draw();

    player_colision_.Render();

    if (attack_flg_) {
        player_attack_collision_model_->SetPosition(player_attack_collision_.Center);
        player_attack_collision_model_->SetRotationQuaternion(player_collision_.Orientation);
        player_attack_collision_model_->Draw();
    }
}

void Player::Render2D() {
    DX9::SpriteBatch->DrawString(
        font.Get(),
        SimpleMath::Vector2(0.0f, 30.0f),
        DX9::Colors::Red,
        L"ÉvÉåÉCÉÑÅ[:%i", player_hp_
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
    player_hp_ -= 1;
    hit_flag_ = true;
}