#include "Classes/Ground/Ground.h"
#include "Classes/Collision/ObjectManager.h"

void Ground::LoadAssets() {
    stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/Stage/stage.X");
    stage_->SetPosition(SimpleMath::Vector3::Zero);
    stage_->SetScale(STAGE_SCALE_);

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

}