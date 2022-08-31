#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

void Ground::LoadAssets() {
    stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage.X");
    stage_->SetPosition(SimpleMath::Vector3(STAGE_POS_X_, 0.0f, STAGE_POS_Z_));
    stage_->SetScale(STAGE_SCALE_);

    bg_   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/BossBattleBG.png");
    mist_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BG/Mist.png");

    bgm_main_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/game_main.mp3");
    bgm_main_->Play();
}

void Ground::Update(const float deltaTime, ObjectManager* object) {
    if (bgm_main_->isComplete()) {
        bgm_main_->Replay();
    }
}

void Ground::Render() {
    stage_->Draw();
}

void Ground::Render2D() {
    DX9::SpriteBatch->DrawSimple(
        bg_.Get(),
        SimpleMath::Vector3(0.0f, 0.0f, BOSS_BG_POS_Z_)
    );
    DX9::SpriteBatch->DrawSimple(
        mist_.Get(),
        SimpleMath::Vector3(mist_pos_.x, mist_pos_.y, MIST_POS_Z_)
    );
}