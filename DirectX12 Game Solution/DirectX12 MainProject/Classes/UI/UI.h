/**
* @file UI.h
* @brief UI�����N���X
* @outhor ���㏃��
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
* @UI�N���X��`
*/
class UI {
public:
	UI() {
		time_delta_ = 0.0f;
		for (int i = 0; i < CHARACTER_MAX_; i++) {
			side_shake_state_[i]	 = 0;
			vertical_shake_state_[i] = 0;
			hp_init_pos_x_[i] = 0.0f;
			hp_init_pos_y_[i] = 0.0f;
			hp_width_[i] = 0.0f;
			old_hp_[i]	 = 0.0f;
			ui_shake_time_[i]	  = 0.0f;
			ui_shake_time_max_[i] = 0.0f;
			ui_side_shake_pos_min_[i] = 0.0f;
			ui_side_shake_pos_max_[i] = 0.0f;
			ui_vertical_shake_pos_min_[i] = 0.0f;
			ui_vertical_shake_pos_max_[i] = 0.0f;
			ui_side_shake_power_[i]		= 0.0f;
			ui_vertical_shake_power_[i] = 0.0f;
			is_damage_[i] = false;
			hp_pos_[i] = SimpleMath::Vector3::Zero;
		}
	}
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render() const;

private:
	void ReadFile();
	void UIShake();

	enum { CHARACTER_MAX_ = 2 }; /**< �L�����N�^�[�̍ő吔 */
	DX9::SPRITE hp_top_[CHARACTER_MAX_]; /**< HP���^���摜�i�[ */
	DX9::SPRITE hp_bottom_[CHARACTER_MAX_]; /**< HP��摜�i�[ */
	
	int side_shake_state_[CHARACTER_MAX_]; /**< HP���h���� */
	int vertical_shake_state_[CHARACTER_MAX_]; /**< HP�c�h���� */
	float time_delta_; /**< ���� */
	float hp_init_pos_x_[CHARACTER_MAX_]; /**< HP�̏���X���W */
	float hp_init_pos_y_[CHARACTER_MAX_]; /**< HP�̏���Y���W */
	float hp_width_[CHARACTER_MAX_]; /**< HP�̉��� */
	float old_hp_[CHARACTER_MAX_]; /**< �ߋ���HP�i�[ */
	float ui_shake_time_[CHARACTER_MAX_]; /**< HP�h�炷���� */
	float ui_shake_time_max_[CHARACTER_MAX_]; /**< UI�h�炷�ő厞�� */
	float ui_side_shake_pos_min_[CHARACTER_MAX_]; /**< UI�h�炷�ŏ�X���W */
	float ui_side_shake_pos_max_[CHARACTER_MAX_]; /**<UI�h�炷�ő�X���W */
	float ui_vertical_shake_pos_min_[CHARACTER_MAX_]; /**< UI�h�炷�ŏ�Y���W */
	float ui_vertical_shake_pos_max_[CHARACTER_MAX_]; /**< UI�h�炷�ő�Y���W */
	float ui_side_shake_power_[CHARACTER_MAX_]; /**< UI�������ɗh�炷���� */
	float ui_vertical_shake_power_[CHARACTER_MAX_]; /**< UI�c�����ɗh�炷���� */	
	bool is_damage_[CHARACTER_MAX_]; /**< �_���[�W���󂯂��� */
	SimpleMath::Vector3 hp_pos_[CHARACTER_MAX_]; /**< HP���W�i�[ */

	/**< �L�����N�^�[�̎�� */
	enum  CHARACTER {
		PLAYER, /**< �v���C���[ */
		BOSS /**< �{�X */
	};

	/**< UI�h����� */
	enum SHAKE_STATE_ {
		UP, /**< �� */
		DOWN, /**< �� */
		RIGHT, /**< �E */
		LEFT /**< �� */
	};

	const int HP_HIGHT_ = 30; /**< HP�摜�̍��� */
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f; /**< �v���C���[HP1/30�̉��� */
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f; /**< �{�XHP1/30�̉��� */
	const float HP_SPEED_ = 300.0f; /**< HP�̑������x */
};