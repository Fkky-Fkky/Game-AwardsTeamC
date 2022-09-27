/**
* @file Ground.h
* @brief �X�e�[�W�ABGM�̏����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

class ObjectManager;

using namespace DirectX;

/**
* @brief Ground�N���X��`
*/
class Ground {
public:
	Ground() { 
		mist_pos_ = SimpleMath::Vector3(MIST_INIT_POS_X_, 0.0f, MIST_INIT_POS_Z_);
		is_frist_battle_ = false;
		first_bg_alpha_ = COLOR_MAX_;
		miset_speed_ = MIST_MOVE_SPEED_SLOW_;
		first_bgm_volume_ = 0.0f;
	}
	~Ground() {};

	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

private:
	void BGMChange(const float deltaTime);

	DX9::MODEL stage_; /**< �X�e�[�W���f���i�[ */
	DX9::SPRITE first_bg_; /**< �O����w�i�i�[ */
	DX9::SPRITE second_bg_; /**< �㔼��w�i�i�[ */
	DX9::SPRITE mist_; /**< ���w�i�i�[ */
	DX9::MEDIARENDERER first_battle_bgm_; /**< �O����BGM�i�[ */
	DX9::MEDIARENDERER second_battle_bgm_; /**< �㔼��BGM�i�[ */

	float first_bg_alpha_; /**< �O����w�i�̃A���t�@�l�i�[ */
	float miset_speed_; /**< ���̓������x�i�[ */
	float first_bgm_volume_; /**< �O����BGM�̉��ʊi�[ */
	bool is_frist_battle_; /**< �O���킩 */
	SimpleMath::Vector3 mist_pos_; /**< ���̍��W�i�[ */

	const float STAGE_POS_X_ = 35.0f; /**< �X�e�[�W��X���W */
	const float STAGE_POS_Z_ = -40.0f; /**< �X�e�[�W��Z���W */
	const float STAGE_SCALE_ = 7.0f; /**< �X�e�[�W���f���̑傫�� */
	const float FIRST_BG_POS_Z_ = 10000.0f; /**< �O����w�i��Z���W */
	const float SECOND_BG_POS_Z_ = 9999.0f; /**< �㔼��w�i��Z���W */
	const float MIST_INIT_POS_Z_ = 9998.0f; /**< ����Z���W */
	const float MIST_INIT_POS_X_ = -1280.0f; /**< ���̏���X���W */
	const float MIST_MOVE_SPEED_SLOW_ = 100.0f; /**< ���̈ړ����x(�x��) */
	const float MIST_MOVE_SPEED_QUICK_ = 200.0f; /**< ���̈ړ����x(����) */
	const float ADD_MIST_SPEED_  = 80.0f; /**< ���̉����x */
	const float ADD_ALPHA_SPEED_ = 300.0f; /**< �A���t�@�l�̑������x */
	const float COLOR_MAX_ = 255.0f; /**< �F�̍ő�l */
	const float SPRITE_WIDTH_ = 1280.0f; /**< �摜�̍ő剡�� */
	const float SPRITE_HIGHT_ = 720.0f; /**< �摜�̍ő�c�� */
	const float BOSS_HP_HALF_ = 15.0f; /**< �{�X��HP�̔��� */
	const float VOLUME_SPEED_ = 900.0f; /**< ���ʌ������x */
	const float VOLUME_MIN_ = -2000.0f; /**< ���ʂ̍ŏ��l */
};