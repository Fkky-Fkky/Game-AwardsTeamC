#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

void Ground::LoadAssets() {
    stage_flooring_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/Flooring/flooring.X");
    stage_bed_      = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/Bet/bet.X");
    building_block  = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Ground/Stage/Flooring/object1.X");
    building_block->SetTrackEnable(0, true);

    //crack_[3] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware1.png");
    //crack_[2] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware2.png");
    //crack_[1] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware3.png");
    //crack_[0] = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Ground/BackGround/hibiware4.png");
    
    bgm_main_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/game_main.mp3");
    bgm_main_->Play();
}

void Ground::Update(const float deltaTime, ObjectManager* object) {
    building_block->AdvanceTime(deltaTime);

    if (bgm_main_->isComplete())
        bgm_main_->Replay();

    int boss_hp_ = object->GetBossHP();

    const int TEN = 10;
    crack_level_ = boss_hp_ / TEN;
}

void Ground::Render() {
    stage_bed_->SetPosition(SimpleMath::Vector3(0.0f, BED_POS_Y_, BED_POS_Z_));
    stage_bed_->Draw();

    stage_flooring_->SetPosition(SimpleMath::Vector3::Zero);
    stage_flooring_->Draw();

    building_block->SetPosition(SimpleMath::Vector3::Zero);
    building_block->Draw();
}

void Ground::Render2D() {
    //DX9::SpriteBatch->DrawSimple(
    //    crack_[crack_level_].Get(),
    //    SimpleMath::Vector3(0.0f, 0.0f, CRACK_POS_Z_)
    //);
}