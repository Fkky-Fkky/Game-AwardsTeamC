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

}

// Allocate all memory the Direct3D and Direct2D resources.
void GameOverScene::LoadAssets()
{
    scene_base_.LoadAssets();
    // グラフィックリソースの初期化処理
    game_over_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/GameOver.png");
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
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

    if (DXTK->KeyEvent->pressed.Enter)
        return NextScene::TitleScene;

	return NextScene::Continue;
}

// Draws the scene.
void GameOverScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(0, 0, 0, 255)));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->DrawSimple(
        game_over_.Get(),
        SimpleMath::Vector3::Zero
    );

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    scene_base_.Render();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}