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
		text_alpha_ = 0;
		text_pos_ = SimpleMath::Vector3::Zero;
	}

	void LoadAssets();
	virtual void Render()const;

	void LoadBG(const LPCWSTR bg_file);
	void RenderBG()const;
	void SetTextPosY(const float init_pos_y);
	void LoadText(const LPCWSTR text_file);
	void UpdateText(const float deltaTime);
	void RenderText()const;
	void SetBGM(const LPCWSTR bgm_file);
	void PlayBGM()const;
	void FadeOutBGM(const float deltaTime);

	/*
	* @biref テキストのアルファ値が最大(255)になったか
	* 
	* @retval TRUE アルファ値が最大
	* @retval FALSE アルファ値が最大ではない
	*/
	bool IsTextAlphaMax()const { return text_alpha_ >= COLOR_MAX_; }
private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	DX9::SPRITE bg_; /**< 背景画像格納 */
	DX9::SPRITE text_; /**< テキスト画像格納 */
	DX9::MEDIARENDERER bgm_; /**< BGM格納 */

	int text_alpha_; /**< テキストのアルファ値 */
	float volume_; /**< BGMの音量格納 */
	SimpleMath::Vector3 text_pos_; /**< テキストの座標 */
	
	const int TEXT_WIDTH_  = 1200; /**< テキスト画像の幅 */
	const int TEXT_HIGHT_  = 300; /**< テキスト画像の高さ */
	const int ALPHA_SPEED_ = 300; /**< アルファ値増減速度 */
	const float TEXT_POS_X_ = 40.0f; /**< テキストのX座標 */
	const float MOVE_SPEED_  = 20.0f; /**< テキストの移動速度 */
	const float MOVE_DEST_Y_ = 210.0f; /**< テキストの移動先 */
	const float VOLUME_DOWN_SPEED_ = 800.0f; /**< 音量を下げる速度 */
	const float VOLUME_MIN_ = -2000.0f; /**< 音量の最低値 */

protected:
	const int COLOR_MAX_ = 255; /**< 色の最大値 */
};