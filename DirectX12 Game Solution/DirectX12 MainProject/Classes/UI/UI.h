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
		player_side_shake_	   = 0;
		player_vertical_shake_ = 0;
		boss_side_shake_	 = 0;
		boss_vertical_shake_ = 0;
		player_hp_width_ = 0.0f;
		boss_hp_width_	 = 0.0f;
		time_delta_		 = 0.0f;
		old_player_hp_	 = 0.0f;
		old_boss_hp_	 = 0.0f;
		player_shake_time_ = 0.0f;
		boss_shake_time_   = 0.0f;
		is_player_damage_ = false;
		is_boss_damage_	  = false;
		player_hp_pos_ = SimpleMath::Vector3::Zero;
		boss_hp_pos_   = SimpleMath::Vector3::Zero;
	}
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render() const;

private:
	void PlayerUIShake();
	void BossUIShake();

	DX9::SPRITE player_hp_top_; /**< �v���C���[HP���^���摜�i�[ */
	DX9::SPRITE player_hp_bottom_; /**< �v���C���[HP��摜�i�[ */
	DX9::SPRITE boss_hp_top_; /**< �{�XHP���^���摜�i�[ */
	DX9::SPRITE boss_hp_bottom_; /**< �{�XHP��摜�i�[ */
	
	int player_side_shake_; /**< �v���C���[HP���h���� */
	int player_vertical_shake_; /**< �v���C���[HP�c�h���� */
	int boss_side_shake_; /**< �{�XHP���h���� */
	int boss_vertical_shake_; /**< �{�XHP�c�h���� */
	float player_hp_width_; /**< �v���C���[HP�̉��� */
	float boss_hp_width_; /**< �{�XHP�̉��� */
	float time_delta_; /**< ���� */
	float old_player_hp_; /**< �ߋ��̃v���C���[HP�i�[ */
	float old_boss_hp_; /**< �ߋ��̃{�XHP�i�[ */
	float player_shake_time_; /**< �v���C���[HP�h�炷���� */
	float boss_shake_time_; /**< �{�XHP�h�炷���� */
	bool is_player_damage_; /**< �v���C���[���_���[�W���󂯂��� */
	bool is_boss_damage_; /**< �{�X���_���[�W���󂯂��� */
	SimpleMath::Vector3 player_hp_pos_; /**< �v���C���[HP���W�i�[ */
	SimpleMath::Vector3 boss_hp_pos_; /**< �{�XHP���W�i�[ */

	/**< UI�h����� */
	enum SHAKE_STATE_ {
		UP, /**< �� */
		DOWN, /**< �� */
		RIGHT, /**< �E */
		LEFT /**< �� */
	};

	const int PLAYER_HP_HIGHT_ = 30; /**< �v���C���[HP���� */
	const int BOSS_HP_HIGHT_   = 30; /**< �{�XHP���� */
	const float PLAYER_HP_POS_X_ = 50.0f; /**< �v���C���[HP��X���W */
	const float PLAYER_HP_POS_Y_ = 680.0f; /**< �v���C���[HP��Y���W */
	const float BOSS_HP_POS_X_ = 190.0f; /**< �{�XHP��X���W */
	const float BOSS_HP_POS_Y_ = 30.0f; /**< �{�XHP��Y���W */
	const float PLAYER_HP_WIDTH_DIVIDE_ = 11.3f; /**< �v���C���[HP1/30�̉��� */
	const float BOSS_HP_WIDTH_DIVIDE_ = 30.0f; /**< �{�XHP1/30�̉��� */
	const float HP_SPEED_ = 300.0f; /**< HP�̑������x */
};