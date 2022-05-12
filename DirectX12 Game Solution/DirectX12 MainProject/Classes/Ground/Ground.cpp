#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

void Ground::LoadAssets() {
    stage_flooring_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage_flooring.X");
    stage_cloud_    = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage_cloud.X");
    bg_vortex_      = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, L"Ground/BackGround/guryuguryu.wmv");
    bg_vortex_->Play();
}

void Ground::Update(ObjectManager* object) {
    if (bg_vortex_->isComplete())
        bg_vortex_->Replay();

    int boss_hp_ = object->GetBossHP();
}

void Ground::Render() {
    stage_cloud_->SetPosition(SimpleMath::Vector3(0.0f, CLOUD_POS_Y_, 0.0f));
    stage_cloud_->Draw();

    stage_flooring_->SetPosition(SimpleMath::Vector3::Zero);
    stage_flooring_->Draw();
}

void Ground::Render2D()
{
    DX9::SpriteBatch->DrawSimple(
        bg_vortex_->Get(),
        SimpleMath::Vector3(0.0f, VORTEX_POS_Y_, VORTEX_POS_Z_)
    );
}