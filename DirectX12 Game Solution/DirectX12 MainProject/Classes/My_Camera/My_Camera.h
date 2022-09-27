/**
* @file My_Camera.h
* @brief �J�����̏����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class ObjectManager;

/**
* @brief My_Camera�N���X��`
*/
class My_Camera {
public:
	My_Camera() {
		vertical_shake_state_ = Down;
		side_shake_state_	  = Right;
		time_delta_			 = 0.0f;
		vertical_shake_time_ = 0.0f;
		is_vertical_shaking_ = false;
		side_shake_flag_	 = false;
		camera_pos_	= SimpleMath::Vector3::Zero;
	}
	~My_Camera() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

private:
	void VerticalShake();
	void SideShake();

	DX9::CAMERA camera_; /**< �J�����i�[ */

	int vertical_shake_state_; /**< �J�����c�h��̏�� */
	int side_shake_state_; /**< �J�������h��̏�� */
	float time_delta_; /**< ���� */
	float vertical_shake_time_; /**< �c�h�ꂷ�鎞�� */
	bool is_vertical_shaking_; /**< �c�h�ꂵ�Ă��邩 */
	bool side_shake_flag_; /**< ���h�ꂷ�邩�t���O */
	SimpleMath::Vector3 camera_pos_; /**< �J�����̍��W�i�[ */

	/**< �J�����h��̎�� */
	enum SHAKE_STATE_ {
		Up, /**< �� */
		Down, /**< �� */
		Right, /**< �E */
		Left /**< �� */
	};

	const float CAMERA_POS_Y_  = 2.0f; /**< �J������Y���W */
	const float CAMERA_POS_Z_  = -26.0f; /**< �J������Z���W */
	const float LOOK_AT_POS_Y_ = 9.0f; /**< ���ڂ���Y���W */
	const float FOV_Y_  = 45.0f; /**< Y�����̎��� */
	const float ASPECT_ = 16.0f / 9.0f; /**< �A�X�y�N�g�� */
	const float NEAR_Z_ = 1.0f; /**< �J�������f���ŏ�Z�l */
	const float FAR_Z_  = 10000.0f; /**< �J�������f���ő�Z�l */
	const float VERTICAL_SHAKE_POS_MAX_  = 2.0f; /**< �c�h�ꎞ�̍ő�Y���W */
	const float VERTICAL_SHAKE_POS_MIN_  = 0.5f; /**< �c�h�ꎞ�̍ŏ�Y���W�@*/
	const float VERTICAL_SHAKE_POWER_	 = 50.0f; /**< �c�h��̋��� */
	const float VERTICAL_SHAKE_TIME_MAX_ = 0.1f; /**< �c�h�ꂷ�鎞�� */
	const float SIDE_SHAKE_POWER_	= 7.0f; /**< ���h�ꂷ�鋭�� */
	const float SIDE_SHAKE_POS_MIN_ = -0.3f; /**< ���h�ꎞ�̍ŏ�X���W */
	const float SIDE_SHAKE_POS_MAX_ = 0.3f; /**< ���h�ꎞ�̍ő�X���W */
};