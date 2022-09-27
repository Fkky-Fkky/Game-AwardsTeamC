#include "Classes/Ground/Ground.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief モデル、画像、音の読み込み
*/
void Ground::LoadAssets() {
    stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage.X");
    stage_->SetPosition(SimpleMath::Vector3(STAGE_POS_X_, 0.0f, STAGE_POS_Z_));
    stage_->SetScale(STAGE_SCALE_);

    second_bg_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/EnemyBG.png");
    first_bg_  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/BossBattleBG.png");
    mist_     = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/Mist.png");

    first_battle_bgm_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM_SE/BGM/FirstBattle.mp3");
    first_battle_bgm_->Play();

    second_battle_bgm_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM_SE/BGM/SecondBattle.mp3");
}

/**
* @brief 背景の更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void Ground::Update(const float deltaTime, const ObjectManager* const obj_m) {
    is_frist_battle_ = obj_m->GetBossHP() >= BOSS_HP_HALF_;
 
    if (is_frist_battle_) {
        first_bg_alpha_ = std::min(first_bg_alpha_ + ADD_ALPHA_SPEED_ * deltaTime, COLOR_MAX_);
        miset_speed_ = std::max(miset_speed_ - ADD_MIST_SPEED_ * deltaTime, MIST_MOVE_SPEED_SLOW_);
    }
    else {
        first_bg_alpha_ = std::max(first_bg_alpha_ - ADD_ALPHA_SPEED_ * deltaTime, 0.0f);
        miset_speed_ = std::min(miset_speed_ + ADD_MIST_SPEED_ * deltaTime, MIST_MOVE_SPEED_QUICK_);
        second_battle_bgm_->Play();
    }

    mist_pos_.x += miset_speed_ * deltaTime;
    if (mist_pos_.x >= 0.0f) {
        mist_pos_.x  = MIST_INIT_POS_X_;
    }

    BGMChange(deltaTime);
}

/**
* @brief ステージの描画
*/
void Ground::Render() const {
    stage_->Draw();
}

/**
* @brief 画像の描画
*/
void Ground::Render2D() const {
    DX9::SpriteBatch->DrawSimple(
        second_bg_.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, SECOND_BG_POS_Z_),
        RectWH(0, 0, SPRITE_WIDTH_, SPRITE_HIGHT_),
        DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, (int)first_bg_alpha_)
    );

    DX9::SpriteBatch->DrawSimple(
        first_bg_.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, FIRST_BG_POS_Z_)
    );
    
    DX9::SpriteBatch->DrawSimple(
        mist_.Get(),
        SimpleMath::Vector3(mist_pos_)
    );
}

/**
* @brief BGMの変更
* 
* ボスのHPが半分になったらBGMを変更する
* @param[in] deltaTime 時間
*/
void Ground::BGMChange(const float deltaTime) {
    if (is_frist_battle_) {
        if (first_battle_bgm_->isComplete()) {
            first_battle_bgm_->Replay();
        }
    }
    else {
        first_bgm_volume_ = std::max(first_bgm_volume_ - VOLUME_SPEED_ * deltaTime, VOLUME_MIN_);
        first_battle_bgm_->SetVolume((long)first_bgm_volume_);
        if (first_bgm_volume_ <= VOLUME_MIN_) {
            first_battle_bgm_->Stop();
        }

        if (second_battle_bgm_->isComplete()) {
            second_battle_bgm_->Replay();
        }
    }
}