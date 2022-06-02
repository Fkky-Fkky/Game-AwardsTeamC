//
// BossTestScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include <Base/DX12Effekseer.h>

// Initialize member variables.
BossTestScene::BossTestScene()
{

}

// Initialize a variable and audio resources.
void BossTestScene::Initialize()
{
    DX12Effect.Initialize();
    boss_.Initialize();
    camera_.Initialize();
    player_.Initialize();
    collision_.Initialize();
    object_.SetPlayer(&player_);
    object_.SetBoss(&boss_);
    object_.SetCollision(&collision_);
}

// Allocate all memory the Direct3D and Direct2D resources.
void BossTestScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, static_cast<int>(screen::width), static_cast<int>(screen::height),
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();

    // グラフィックリソースの初期化処理

    boss_.LoadAseets();
    player_.LoadAssets();
    ground_.LoadAssets();
    collision_.LoadAssets();
    ui.LoadAssets();
    light_.LoadAssets();
}

// Releasing resources required for termination.
void BossTestScene::Terminate()
{
	DXTK->ResetAudioEngine();
	DXTK->WaitForGpu();

	// TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void BossTestScene::OnDeviceLost()
{
    DX12Effect.Reset();
}

// Restart any looped sounds here
void BossTestScene::OnRestartSound()
{

}

// Updates the scene.
NextScene BossTestScene::Update(const float deltaTime)
{
	// If you use 'deltaTime', remove it.
	UNREFERENCED_PARAMETER(deltaTime);

	// TODO: Add your game logic here.

    player_.Update(deltaTime, &object_);
    boss_.Update(deltaTime, &object_);

    DX12Effect.Update(deltaTime);
    ground_.Update(deltaTime, &object_);
    collision_.Update(deltaTime, &object_);
    scene_change_.Update(&object_);
    ui.Update(deltaTime, &object_);

    if (scene_change_.GetSceneChangeFlag()) {
        return NextScene::ResultScene;
    }

	return NextScene::Continue;
}

// Draws the scene.
void BossTestScene::Render()
{
	// TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(157, 204, 220, 255)));

    DXTK->Direct3D9->BeginScene();

    boss_.Render();
    player_.Render();
    ground_.Render();

    DX9::SpriteBatch->Begin();

    ground_.Render2D();
    collision_.Render2D();
    player_.Render2D();
    boss_.Render2D();
    ui.Render();

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

	DXTK->Direct3D9->UpdateResource();

    DXTK->ResetCommand();
    DXTK->ClearRenderTarget(Colors::CornflowerBlue);

    const auto heapes = descriptorHeap->Heap();
    DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

    spriteBatch->Begin(DXTK->CommandList);
    spriteBatch->Draw(
        dx9GpuDescriptor,
        XMUINT2(static_cast<int>(screen::width), static_cast<int>(screen::height)),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DX12Effect.Renderer();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}
