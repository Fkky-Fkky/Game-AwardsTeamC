//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include <Base/DX12Effekseer.h>

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    DX12Effect.Initialize();
    boss_.Initialize();
    camera_.Initialize();
    player_.Initialize();
    collision_.Initialize();
    scene_change_.Initialize();
    ui.Initialize();
    object_.SetPlayer(&player_);
    object_.SetBoss(&boss_);
    object_.SetCollision(&collision_);
}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, 1280.0f, 720.0f,
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
    scene_change_.LoadAssets();
    ui.LoadAssets();
    light_.LoadAssets();
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}

// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.

    scene_change_.Update(deltaTime, &object_);

    if (scene_change_.IsGameStart()) {
        player_.Update(deltaTime, &object_);
        boss_.Update(deltaTime, &object_);
        camera_.Update(deltaTime, &object_);
        DX12Effect.Update(deltaTime);
        ground_.Update(deltaTime, &object_);
        collision_.Update(deltaTime, &object_);
        ui.Update(deltaTime, &object_);
        light_.Update(deltaTime);
    }
    
    if (scene_change_.GetSceneChangeFlag()) {
        if (scene_change_.IsGameClear()) {
            return NextScene::ClearScene;
        }
        else
        {
            return NextScene::GameOverScene;
        }
    }

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(100, 0, 0, 155));

    DXTK->Direct3D9->BeginScene();

    player_.Render();
    boss_.Render();
    ground_.Render();

    DX9::SpriteBatch->Begin();

    ground_.Render2D();
    collision_.Render2D();
    scene_change_.Render2D();
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