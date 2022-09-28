/**
* @file SceneBase.h
* @brief �e�V�[�����ʏ����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @brief SceneBase�N���X��`
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

	DX9::SPRITE bg_; /**< �摜�i�[ */
	DX9::MEDIARENDERER bgm_; /**< BGM�i�[ */
	float volume_; /**< BGM�̉��ʊi�[ */
	const float VOLUME_DOWN_SPEED_ = 800.0f; /**< ���ʂ������鑬�x */
	const float VOLUME_MIN_ = -2000.0f; /**< ���ʂ̍Œ�l */
};