//
// TitleScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Scene/SceneFactory.h"

// Initialize member variables.
TitleScene::TitleScene()
{
    black_alpha_ = 0;
    start_flag_ = false;
}

// Initialize a variable and audio resources.
void TitleScene::Initialize()
{
    black_alpha_ = 0;
    start_flag_ = false;
    scene_base_.SetTextPosY(TITLE_TEXT_POS_Y_);
}

// Allocate all memory the Direct3D and Direct2D resources.
void TitleScene::LoadAssets()
{
    scene_base_.LoadAssets();
    // グラフィックリソースの初期化処理

    scene_base_.LoadBG(L"Scene/TitleBG.png");
    scene_base_.LoadText(L"Scene/TitleText.png");
    black_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/Black.png");
    scene_base_.SetBGM(L"BGM_SE/BGM/Title.mp3");
}

// Releasing resources required for termination.
void TitleScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void TitleScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void TitleScene::OnRestartSound()
{

}

// Updates the scene.
NextScene TitleScene::Update(const float deltaTime)
{
	// TODO: Add your game logic here.

    scene_base_.PlayBGM();
    scene_base_.UpdateText(deltaTime);

    if (DXTK->KeyEvent->pressed.Enter ||
        DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED) {
        start_flag_ = true;
    }

    if (start_flag_) {
        black_alpha_ += BLACK_ALPHA_SPEED_ * deltaTime;
        if (black_alpha_ > COLOR_MAX_) {
            black_alpha_ = COLOR_MAX_;
        }
        scene_base_.FadeOut(deltaTime);
    }

    if (black_alpha_ >= COLOR_MAX_) {
        return NextScene::MainScene;
    }

	return NextScene::Continue;
}

// Draws the scene.
void TitleScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::CornflowerBlue));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    scene_base_.RenderBG();
    scene_base_.RenderText();

    DX9::SpriteBatch->DrawSimple(
        black_.Get(),
        SimpleMath::Vector3::Zero,
        RectWH(0, 0, WIDTH_MAX_, HIGHT_MAX_),
        DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, black_alpha_)
    );

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    scene_base_.Render();
    
    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}