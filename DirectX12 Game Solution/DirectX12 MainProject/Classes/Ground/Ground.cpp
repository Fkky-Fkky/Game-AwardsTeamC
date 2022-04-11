#include "Classes/Ground/Ground.h"

void Ground::Initialize() {
    
}

void Ground::LoadAssets() {
    stage_ = DX9::Model::CreateFromFile(DXTK->Device9, L"Ground/stage_a.X");
}

void Ground::Render() {
    stage_->SetPosition(SimpleMath::Vector3(0, -2.0f, 0));
    stage_->Draw();
}