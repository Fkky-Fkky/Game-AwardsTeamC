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
    camera.Initialize();
    boss.Intialize();
    size = SimpleMath::Vector2(0.0f,0.0f);
    origin = SimpleMath::Vector3(330.5f, 142.5f, 0.0f);
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
    light.Type      = D3DLIGHT_DIRECTIONAL;
    light.Ambient   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Specular  = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);
    light.Diffuse   = DX9::Colors::Value(1.0f, 1.0f, 1.0f, 1.0f);

    light.Direction = DX9::VectorSet(0.0f, -100.0f, -30.0f);
    DXTK->Direct3D9->SetLight(0, light);

    boss.LoadAseets();

    susi = DX9::Sprite::CreateFromFile(DXTK->Device9, L"susi_zanmai.png");
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

    boss.Update(deltaTime);

    if (DXTK->KeyState->S) {
        size.x += 1.0f * deltaTime;
        size.y += 1.0f * deltaTime;
    }
    if (size.x >= 1.0f) {
        size.x = 1.0f;
        size.y = 1.0f;

    }

    return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    // TODO: Add your rendering code here.
    DXTK->Direct3D9->Clear(DX9::Colors::CornflowerBlue/*RGBA(0, 0, 0, 255)*/);

    DXTK->Direct3D9->BeginScene();

    boss.Render();


    DX9::SpriteBatch->Begin();

    DX9::SpriteBatch->Draw(
        susi.Get(),
        SimpleMath::Vector3(650.0f, 450.0f, 0.0f),
        DX9::Colors::RGBA(255,255,255,255),
        size,
        origin
    );

    boss.Render2D();

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