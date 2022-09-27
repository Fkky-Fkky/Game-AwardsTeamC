/**
* @file Collision.h
* @brief �v���C���[�ƃ{�X�̃R���W���������N���X
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
* @brief Collision�N���X��`
*/
class Collision {
public:
	Collision() {
		hand_dmg_flag_reset_time_ = 0.0f;
		player_dmg_flag_r_ = false;
		player_dmg_flag_l_ = false;
		boss_body_dmg_flg_	  = false;
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
	}
	~Collision() {};

	void Initialize();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);

	/**
	* @brief �v���C���[���E�肩��U�����󂯂���
	* 
	* @retval TRUE �󂯂�
	* @retval FALSE �󂯂Ă��Ȃ�
	*/
	bool GetPlayerDmgFlagR() const { return player_dmg_flag_r_; }

	/**
	* @brief �v���C���[�����肩��U�����󂯂���
	* 
	* @retval TRUE �󂯂�
	* @retval FALSE �󂯂Ă��Ȃ�
	*/
	bool GetPlayerDmgFlagL() const { return player_dmg_flag_l_; }

	/**
	* @brief �{�X�̖{�̂��_���[�W���󂯂���
	* 
	* @retval TRUE �󂯂�
	* @retval FALSE �󂯂Ă��Ȃ�
	*/
	bool IsBossBodyDmg() const { return boss_body_dmg_flg_; }

	/**
	* @brief �{�X�̎肪�_���[�W���󂯂���
	* 
	* @retval TRUE �󂯂�
	* @retval FALSE �󂯂Ă��Ȃ�
	*/
	bool IsBossHandDmg() const { return boss_hand_r_dmg_flag_ || boss_hand_l_dmg_flag_; }

private:
	float hand_dmg_flag_reset_time_; /**< ��̃_���[�W�t���O���~�낷���� */
	bool player_dmg_flag_r_; /**< �v���C���[���E�肩��U�����󂯂��� */
	bool player_dmg_flag_l_; /**< �v���C���[�����肩��U�����󂯂��� */
	bool boss_body_dmg_flg_; /**< �{�X�{�̂��_���[�W���󂯂��� */
	bool boss_hand_r_dmg_flag_; /**< �{�X�E�肪�_���[�W���󂯂���*/
	bool boss_hand_l_dmg_flag_; /**< �{�X���肪�_���[�W���󂯂���*/
};