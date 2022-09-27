/**
* @file DoubleSlap.h
* @brief ����ガ�����U�������N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief DoubleSlap�N���X��`
	*/
	class DoubleSlap : public BossAction {
	public:
		DoubleSlap() {
			action_state_ = HAND_CHECK;
			time_delta_ = 0.0f;
			slap_y_		= 0.0f;
			l_slap_speed_x_ = 0.0f;
			wait_time_		= 0.0f;
			ready_end_r_ = false;
			ready_end_l_ = false;
			atk_end_r_ = false;
			atk_end_l_ = false;
			return_end_r_ = false;
			return_end_l_ = false;
			hand_state_ = false;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_pos_ = SimpleMath::Vector3::Zero;
		}

		~DoubleSlap() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(ActionManager* const act_m);
		void ReadyR();
		void ReadyL();
		void Attack(ActionManager* const act_m);
		void SlapR(ActionManager* const act_m);
		void SlapL();
		void Reset();
		void HandReturn();

		int action_state_; /**< ���݂̍U���s���i�[ */

		float time_delta_; /**< ���� */
		float slap_y_; /**< �\���ɕK�v�ȏ����i�[ */
		float l_slap_speed_x_; /**< ���ガ�����X�s�[�h�i�[ */
		float wait_time_; /**< �ҋ@���Ԋi�[ */

		bool ready_end_r_; /**< �E��\�������������� */
		bool ready_end_l_; /**< ����\�������������� */
		bool atk_end_r_; /**< �E��̍U�������������� */
		bool atk_end_l_; /**< ����̍U�������������� */
		bool return_end_r_; /**< �E�肪�������W�Ɉړ������� */
		bool return_end_l_; /**< ���肪�������W�Ɉړ������� */
		bool hand_state_; /**< ��̏�Ԋi�[ */

		SimpleMath::Vector3 r_pos_; /**< �E��̍��W�i�[ */
		SimpleMath::Vector3 l_pos_; /**< ����̍��W�i�[ */

		const float L_HAND_DEST_Y_ = 8.0f; /**< ����̈ړ���Y���W */
		const float ATTACK_START_TIME_R_ = 1.0f; /**< �E��̍U���J�n���� */
		const float WAIT_TIME_MAX_ = 1.5f; /**< �ő�ҋ@���� */
	};
}