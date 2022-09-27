//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include <Base/DX12Effekseer.h>

// Initialize member variables.
MainScene::MainScene() 
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
    scene_base_.LoadAssets();

    // グラフィックリソースの初期化処理
    boss_.LoadAseets();
    player_.LoadAssets();
    ground_.LoadAssets();
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
    }
    
    if (scene_change_.IsSceneChange()) {
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
    scene_change_.Render2D();
    ui.Render();

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    scene_base_.Render(); 
    DX12Effect.Renderer();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}