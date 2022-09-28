/**
* @file SceneBase.h
* @brief 各シーン共通処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @brief SceneBaseクラス定義
*/
class SceneBase {
public:
	SceneBase() {
		dx9GpuDescriptor = {};
		volume_ = 0;
	}

	void LoadAssets();
	void Render()const;

	void LoadBG(const LPCWSTR bg_file);
	void RenderBG()const;
	void SetBGM(const LPCWSTR bgm_file);
	void PlayBGM()const;
	void FadeOut(const float deltaTime);
private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	DX9::SPRITE bg_; /**< 画像格納 */
	DX9::MEDIARENDERER bgm_; /**< BGM格納 */
	float volume_; /**< BGMの音量格納 */
	const float VOLUME_DOWN_SPEED_ = 800.0f; /**< 音量を下げる速度 */
	const float VOLUME_MIN_ = -2000.0f; /**< 音量の最低値 */
};