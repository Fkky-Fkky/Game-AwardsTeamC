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
* @brief 背景画像読み込み
* 
* @param[in] bg_file 画像ファイル名
*/
void SceneBase::LoadBG(const LPCWSTR bg_file) {
    bg_ = DX9::Sprite::CreateFromFile(DXTK->Device9, bg_file);
}

/**
* @brief 背景画像描画
*/
void SceneBase::RenderBG() const {
    DX9::SpriteBatch->DrawSimple(
        bg_.Get(),
        SimpleMath::Vector3::Zero
    );
}

/**
* @brief テキストの座標設定
* 
* @param[in] init_pos 初期Y座標
*/
void SceneBase::SetTextPosY(const float init_pos) {
    text_pos_  = SimpleMath::Vector3(TEXT_POS_X_, init_pos, 0.0f);
}

/**
* @brief テキスト画像ファイル読み込み
* 
* @param[in] text_file 画像ファイル名
*/
void SceneBase::LoadText(const LPCWSTR text_file) {
    text_ = DX9::Sprite::CreateFromFile(DXTK->Device9, text_file);
}

/**
* @brief テキストの更新
* 
* @param[in] deltaTime 時間
*/
void SceneBase::UpdateText(const float deltaTime) {
    if (text_pos_.y > MOVE_DEST_Y_) {
        text_pos_.y = std::max(text_pos_.y - MOVE_SPEED_ * deltaTime, MOVE_DEST_Y_);
    }
    else {
        text_pos_.y = std::min(text_pos_.y + MOVE_SPEED_ * deltaTime, MOVE_DEST_Y_);
    }

    text_alpha_ += ALPHA_SPEED_ * deltaTime;
    if (text_alpha_ >= COLOR_MAX_) {
        text_alpha_  = COLOR_MAX_;
    }
}

/**
* @brief テキスト画像の描画
*/
void SceneBase::RenderText() const {
    DX9::SpriteBatch->DrawSimple(
        text_.Get(),
        text_pos_,
        RectWH(0, 0, TEXT_WIDTH_, TEXT_HIGHT_),
        DX9::Colors::RGBA(COLOR_MAX_, COLOR_MAX_, COLOR_MAX_, text_alpha_)
    );
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

/**
* @brief BGMのフェードアウト
* 
* @param[in] deltaTime 時間
*/
void SceneBase::FadeOutBGM(const float deltaTime) {
    volume_ = std::max(volume_ - VOLUME_DOWN_SPEED_ * deltaTime, VOLUME_MIN_);
    bgm_->SetVolume(volume_);
}