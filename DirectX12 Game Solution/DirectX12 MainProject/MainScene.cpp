//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"

// Initialize member variables.
MainScene::MainScene() : dx9GpuDescriptor{}
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //camera.Initialize();
    player_camera.Initialize();
    player.Initialize();
    boss.Initialize();
    smallEnemy.Initialize();
    collision.Initialize();
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
    D3DLIGHT9 light{};
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Ambient = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Specular = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Diffuse = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);

    light.Direction = DX9::VectorSet(0.0f, -10.0f, 5.0f);
    DXTK->Direct3D9->SetLight(0, light);

    player.LoadAssets();
    ground.LoadAssets();
    boss.LoadAseets();
    smallEnemy.LoadAssets();
    collision.LoadAssets();
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

    player.Update(deltaTime);
    player.HitPlayer(object.GetPlayerDmgFlag());
    boss.Update(deltaTime, &object);
    //smallEnemy.HitPlayerAttack(collision.GetHitAttackFlag());
    //smallEnemy.Update(deltaTime);
    collision.Update(deltaTime, &object);

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(157, 204, 220, 255));

    DXTK->Direct3D9->BeginScene();

    player.Render();
    ground.Render();
    boss.Render();
    smallEnemy.Render();

    DX9::SpriteBatch->Begin();

    collision.Render2D();
    player.Render2D();
    smallEnemy.Render2D();



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
        XMUINT2(1280, 720),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}