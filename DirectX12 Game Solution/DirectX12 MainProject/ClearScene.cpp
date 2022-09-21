//
// ClearScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
ClearScene::ClearScene()
{

}

// Initialize a variable and audio resources.
void ClearScene::Initialize()
{

}

// Allocate all memory the Direct3D and Direct2D resources.
void ClearScene::LoadAssets()
{
    scene_base_.LoadAssets();
    // グラフィックリソースの初期化処理
    clear_ = DX9::Sprite::CreateFromFile(DXTK->Device9, L"Scene/GameClear.png");
}

// Releasing resources required for termination.
void ClearScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void ClearScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void ClearScene::OnRestartSound()
{

}

// Updates the scene.
NextScene ClearScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

    if (DXTK->KeyEvent->pressed.Enter)
        return NextScene::TitleScene;

	return NextScene::Continue;
}

// Draws the scene.
void ClearScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(0, 0, 0, 255)));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->DrawSimple(
        clear_.Get(),
        SimpleMath::Vector3::Zero
    );

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    scene_base_.Render();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}