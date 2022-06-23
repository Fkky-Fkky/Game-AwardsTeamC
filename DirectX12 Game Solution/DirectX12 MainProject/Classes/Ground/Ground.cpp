#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

void Ground::LoadAssets() {
    stage_flooring_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/Flooring/flooring.X");
    stage_flooring_->SetPosition(SimpleMath::Vector3::Zero);

    stage_bed_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/Bet/bet.X");
    stage_bed_->SetPosition(SimpleMath::Vector3(0.0f, BED_POS_Y_, BED_POS_Z_));

    building_block = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, L"Ground/Stage/Flooring/object1.X");
    building_block->SetPosition(SimpleMath::Vector3::Zero);
    building_block->SetTrackEnable(0, true);

    castle = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/Castle/castle.X");
    //castle->SetPosition(SimpleMath::Vector3(0.0f, CASTLE_POS_Y_, BED_POS_Z_));
    //castle->SetScale(0.7f);

    bgm_main_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"BGM/game_main.mp3");
    bgm_main_->Play();
}

void Ground::Update(const float deltaTime, ObjectManager* object) {
    building_block->AdvanceTime(deltaTime);

    if (bgm_main_->isComplete()) {
        bgm_main_->Replay();
    }
}

void Ground::Render() {
    stage_bed_->Draw();
    stage_flooring_->Draw();
    building_block->Draw();
    //castle->Draw();
}

void Ground::Render2D() {

}