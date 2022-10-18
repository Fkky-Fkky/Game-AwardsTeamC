#include "Classes/GameScene/ResultSceneBase.h"

/**
* @brief BGMの再生とテキストの移動
* 
* @param[in] deltaTIme 時間
*/
void ResultSceneBase::Update(const float deltaTime) {
	SceneBase::PlayBGM();
	SceneBase::UpdateText(deltaTime);
}

/**
* @brief 画像の描画処理
*/
void ResultSceneBase::Render() const {
    DXTK->Direct3D9->Clear(static_cast<D3DCOLOR>(DX9::Colors::RGBA(0, 0, 0, COLOR_MAX_)));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    SceneBase::RenderBG();
    SceneBase::RenderText();

    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    SceneBase::Render();

    DXTK->Direct3D9->WaitUpdate();
    DXTK->ExecuteCommandList();
}
