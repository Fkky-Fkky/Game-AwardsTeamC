#include "Classes/Ground/Ground.h"
#include "Classes/Object/ObjectManager.h"

void Ground::LoadAssets() {
    stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage.X");
    stage_->SetPosition(SimpleMath::Vector3(STAGE_POS_X_, 0.0f, STAGE_POS_Z_));
    stage_->SetScale(STAGE_SCALE_);

    enemy_bg_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/EnemyBG.png");
    boss_bg_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/BossBattleBG.png");
    mist_     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/Mist.png");

    bgm_main_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/game_main.mp3");
    bgm_main_->Play();
}

void Ground::Update(const float deltaTime, const ObjectManager* const obj_m) {
    if (bgm_main_->isComplete()) {
        bgm_main_->Replay();
    }

    bg_change_flag_ = obj_m->GetBossHP() <= BOSS_HP_HALF_;
    
    if (bg_change_flag_) {
        enemy_bg_alpha_ = std::max(enemy_bg_alpha_ - ADD_ALPHA_SPEED_ * deltaTime, 0.0f);
        miset_speed_ = std::min(miset_speed_ + ADD_MIST_SPEED_ * deltaTime, MIST_MOVE_SPEED_QUICK_);
    }
    else {
        enemy_bg_alpha_ = std::min(enemy_bg_alpha_ + ADD_ALPHA_SPEED_ * deltaTime, COLOR_MAX_);
        miset_speed_ = std::max(miset_speed_ - ADD_MIST_SPEED_ * deltaTime, MIST_MOVE_SPEED_SLOW_);
    }

    mist_pos_.x += miset_speed_ * deltaTime;
    if (mist_pos_.x >= 0.0f) {
        mist_pos_.x  = MIST_INIT_POS_X_;
    }
}

void Ground::Render() const {
    stage_->Draw();
}

void Ground::Render2D() const {
    DX9::SpriteBatch->DrawSimple(
        enemy_bg_.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, ENEMY_BG_POS_Z_),
        RectWH(0, 0, SPRITE_WIDTH_, SPRITE_HIGHT_),
        DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, (int)enemy_bg_alpha_)
    );

    DX9::SpriteBatch->DrawSimple(
        boss_bg_.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, BOSS_BG_POS_Z_)
    );
    
    DX9::SpriteBatch->DrawSimple(
        mist_.Get(),
        SimpleMath::Vector3(mist_pos_)
    );
}