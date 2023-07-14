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
	* @biref �e�L�X�g�̃A���t�@�l���ő�(255)�ɂȂ�����
	* 
	* @retval TRUE �A���t�@�l���ő�
	* @retval FALSE �A���t�@�l���ő�ł͂Ȃ�
	*/
	bool IsTextAlphaMax()const { return text_alpha_ >= COLOR_MAX_; }
private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	DX9::SPRITE bg_; /**< �w�i�摜�i�[ */
	DX9::SPRITE text_; /**< �e�L�X�g�摜�i�[ */
	DX9::MEDIARENDERER bgm_; /**< BGM�i�[ */

	int text_alpha_; /**< �e�L�X�g�̃A���t�@�l */
	float volume_; /**< BGM�̉��ʊi�[ */
	SimpleMath::Vector3 text_pos_; /**< �e�L�X�g�̍��W */
	
	const int TEXT_WIDTH_  = 1200; /**< �e�L�X�g�摜�̕� */
	const int TEXT_HIGHT_  = 300; /**< �e�L�X�g�摜�̍��� */
	const int ALPHA_SPEED_ = 300; /**< �A���t�@�l�������x */
	const float TEXT_POS_X_ = 40.0f; /**< �e�L�X�g��X���W */
	const float MOVE_SPEED_  = 20.0f; /**< �e�L�X�g�̈ړ����x */
	const float MOVE_DEST_Y_ = 210.0f; /**< �e�L�X�g�̈ړ��� */
	const float VOLUME_DOWN_SPEED_ = 800.0f; /**< ���ʂ������鑬�x */
	const float VOLUME_MIN_ = -2000.0f; /**< ���ʂ̍Œ�l */

protected:
	const int COLOR_MAX_ = 255; /**< �F�̍ő�l */
};