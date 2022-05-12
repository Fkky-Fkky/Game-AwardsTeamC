#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

Ground::Ground() {
    crack_level_ = 0;
}

void Ground::LoadAssets() {
    stage_flooring_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage_flooring.X");
    stage_bed_      = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/bet.X");
    crack_[3] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware1.png");
    crack_[2] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware2.png");
    crack_[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware3.png");
    crack_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware4.png");
    //bg_vortex_      = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"Ground/BackGround/guryuguryu.wmv");
    //bg_vortex_->Play();
}

void Ground::Update(ObjectManager* object) {
    //if (bg_vortex_->isComplete())
    //    bg_vortex_->Replay();

    int boss_hp_ = object->GetBossHP();
    
    crack_level_ = boss_hp_ / 10;
}

void Ground::Render() {
    stage_bed_->SetPosition(SimpleMath::Vector3(0.0f, BED_POS_Y_, BED_POS_Z_));
    stage_bed_->Draw();

    stage_flooring_->SetPosition(SimpleMath::Vector3::Zero);
    stage_flooring_->Draw();
}

void Ground::Render2D() {
    DX9::SpriteBatch->DrawSimple(
        crack_[crack_level_].Get(),
        SimpleMath::Vector3(0.0f, 0.0f, CRACK_POS_Z_)
    );

    //DX9::SpriteBatch->DrawSimple(
    //    bg_vortex_->Get(),
    //    SimpleMath::Vector3(0.0f, VORTEX_POS_Y_, VORTEX_POS_Z_)
    //);
}