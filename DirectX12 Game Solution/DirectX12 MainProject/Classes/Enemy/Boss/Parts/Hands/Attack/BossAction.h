/**
* @file BossAction.h
* @brief �{�X�̍s�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include "Base/DX12Effekseer.h"

/**
* �N���X�Q��
*/
class ObjectManager;
class ActionManager;

using namespace DirectX;

namespace boss {
	/**
	* @brief BossAction��`
	*/
	class BossAction {
	public:
		BossAction() {
			slap_speed_  = 0.0f;
			slap_y_time_ = 0.0f;
			is_se_play_	  = false;
			is_shake_set_ = false;
			boss_handL_ = nullptr;
			boss_handR_ = nullptr;
		}

		virtual void Initialize(BossHand* const boss_handL, BossHand* const boss_handR);
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) = 0;

	private:
		float slap_y_time_; /**< �ガ�����\�����̎��� */
		bool is_se_play_; /**< SE���Đ������� */
		bool is_shake_set_; /**< �J�������h��ݒ肵���� */
		const float SLAP_SPEED_Y_	= 2.0f; /**< �ガ�����\���̑��x */
		const float SLAP_GRAVITY_Y_ = 5.0f; /**< �ガ�����\���̏d�� */

	protected:
		virtual void SlapAttackBase(const float deltaTime, ActionManager* const act_m);
		virtual float SlapY(const float deltaTime);

		BossHand* boss_handL_; /**< �{�X����i�[ */
		BossHand* boss_handR_; /**< �{�X�E��i�[ */
		float slap_speed_; /**< �ガ�����U���̃X�s�[�h�i�[ */


		const float HAND_R_INITIAL_POS_X_ = -13.0f; /**< �E��̏���X���W */
		const float HAND_L_INITIAL_POS_X_ = 13.0f; /**< ����̏���X���W */
		const float HAND_INITIAL_POS_Y_ = 13.0f; /**< ��̏���Y���W */
		const float HAND_INITIAL_POS_Z_ = 10.0f; /**< ��̏���Z���W */

		const float HAND_INITIAL_ROT_X_ = 30.0f; /**< ��̏�����]X�� */

		const float ATTACK_POS_Z_ = -2.0f; /**< �U������Z���W */
		const float HAND_LIMIT_POS_X_ = 70.0f; /**< ��̍ő�ړ�X�͈�*/
		const float HAND_ROCK_LIMIT_POS_Y_ = 3.0f; /**< �般���Ԏ��̍ő�ړ�Y�͈� */
		const float HAND_RETURN_POS_X_ = 30.0f; /**< �肪�����ʒu�ɖ߂鎞�̃X�^�[�gX���W */

		const float SLAP_POS_Y_ = 0.5f; /**< �ガ�����U������Y���W */
		const float SLAP_SPEED_MAX_X_ = 40.0f; /**< �ガ�����U�����̍ő呬�x */
		const float ADD_SLAP_SPEED_ = 20.0f; /**< �ガ�����U���̉����x */

		const float WAIT_TIME_MAX_ = 0.7f; /**< �ҋ@���� */

		const float BEAT_SPEED_ = 3.5f; /**< �@�����U���̃X�s�[�h */
		const float BEAT_GRAVITY_ = 15.0f; /**< �@�����U���̏d�� */
		const float BEAT_HAND_ROCK_ROT_X_ = 90.0f; /**< �般���Ԏ��̉�]X�� */

		const float MOVE_SPEED_X_ = 20.0f; /**< X���W�ړ����x */
		const float MOVE_SPEED_Y_ = 10.0f; /**< Y���W�ړ����x */
		const float MOVE_SPEED_Z_ = 20.0f; /**< Z���W�ړ����x */
		const float ROTE_SPEED_ = 200.0f; /**< ��]���x */

		const float HALF_ = 0.5f; /**< ���� */

		/**< �s���̎�� */
		enum ACTION_STATE {
			HAND_CHECK, /**< ��̏�Ԋm�F */
			READY, /**< �\�� */
			WAIT, /**< �ҋ@ */
			ATTACK, /**< �U�� */
			RESET, /**< �l�̃��Z�b�g */
			RETURN, /**< ��������ʒu�ɖ߂� */
			ACTION_END /**< �s���I�� */
		};

		/**< ��̃��[�V���� */
		enum HAND_MOTION {
			WAIT_MOTION, /**< �ҋ@ */
			PAPER, /**< ����J�� */
			PAPER_BACK, /**< �J������Ԃ���ҋ@�֖߂� */
			ROCK, /**< ������� */
			ROCK_BACK /**< ��������Ԃ���ҋ@�֖߂� */
		};
	};
}