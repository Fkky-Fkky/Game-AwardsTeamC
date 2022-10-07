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
		camera_init_pos_x_ = 0.0f;
		camera_init_pos_y_ = 0.0f;
		vertical_shake_pos_max_ = 0.0f;
		vertical_shake_pos_min_ = 0.0f;
		vertical_shake_power_ = 0.0f;
		vertical_shake_time_max_ = 0.0f;
		side_shake_power_ = 0.0f;
		side_shake_pos_min_ = 0.0f;
		side_shake_pos_max_ = 0.0f;
		is_vertical_shaking_ = false;
		side_shake_flag_	 = false;
		camera_pos_	= SimpleMath::Vector3::Zero;
	}
	~My_Camera() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

private:
	void ReadFile();
	void VerticalShake();
	void SideShake();

	DX9::CAMERA camera_; /**< �J�����i�[ */

	int vertical_shake_state_; /**< �J�����c�h��̏�� */
	int side_shake_state_; /**< �J�������h��̏�� */
	float time_delta_; /**< ���� */
	float vertical_shake_time_; /**< �c�h�ꂷ�鎞�Ԋi�[ */
	float camera_init_pos_x_; /**< �J�����̏���X���W*/
	float camera_init_pos_y_; /**< �J�����̏���Y���W */
	float vertical_shake_pos_max_; /**< �c�h�ꎞ�̍ő�Y���W */
	float vertical_shake_pos_min_; /**< �c�h�ꎞ�̍ŏ�Y���W�@*/
	float vertical_shake_power_; /**< �c�h��̋��� */
	float vertical_shake_time_max_; /**< �c�h�ꂷ��ő厞�� */
	float side_shake_power_; /**< ���h�ꂷ�鋭�� */
	float side_shake_pos_min_; /**< ���h�ꎞ�̍ŏ�X���W */
	float side_shake_pos_max_; /**< ���h�ꎞ�̍ő�X���W */

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

	const float FOV_Y_  = 45.0f; /**< Y�����̎��� */
	const float ASPECT_ = 16.0f / 9.0f; /**< �A�X�y�N�g�� */
	const float NEAR_Z_ = 1.0f; /**< �J�������f���ŏ�Z�l */
	const float FAR_Z_  = 10000.0f; /**< �J�������f���ő�Z�l */
};