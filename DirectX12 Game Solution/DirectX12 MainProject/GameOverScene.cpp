//
// GameOverScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
GameOverScene::GameOverScene()
{
}

// Initialize a variable and audio resources.
void GameOverScene::Initialize()
{
    scene_base_.SetTextPosY(TEXT_INIT_POS_Y_);
}

// Allocate all memory the Direct3D and Direct2D resources.
void GameOverScene::LoadAssets()
{
    scene_base_.LoadAssets();
    // グラフィックリソースの初期化処理
    scene_base_.LoadBG(L"Scene/Black.png");
    scene_base_.LoadText(L"Scene/GameOverText.png");
    scene_base_.SetBGM(L"BGM_SE/BGM/GameOver.mp3");
}

// Releasing resources required for termination.
void GameOverScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void GameOverScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void GameOverScene::OnRestartSound()
{

}

// Updates the scene.
NextScene GameOverScene::Update(const float deltaTime)
{
	// TODO: Add your game logic here.
    scene_base_.Update(deltaTime);

    if (DXTK->KeyEvent->pressed.Enter)
        return NextScene::TitleScene;

	return NextScene::Continue;
}

// Draws the scene.
void GameOverScene::Render()
{
	// TODO: Add your rendering code here.
    scene_base_.Render();
}