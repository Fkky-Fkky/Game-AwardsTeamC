#include "SceneBase.h"

/**
* @brief 各シーン共通LoadAssets処理
*/
void SceneBase::LoadAssets() {
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
}

/**
* @brief 各シーン共通Render処理
*/
void SceneBase::Render() const {
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
}

/**
* @brief BGMの読み込み
* 
* @param[in] bgm_file 再生する音楽ファイル名
*/
void SceneBase::SetBGM(const LPCWSTR bgm_file) {
    bgm_ = DX9::MediaRenderer::CreateFromFile(DXTK->Device9, bgm_file);
    bgm_->Play();
}

/**
* @brief BGMの再生処理
*/
void SceneBase::PlayBGM() const {
    if (bgm_->isComplete()) {
        bgm_->Replay();
    }
}