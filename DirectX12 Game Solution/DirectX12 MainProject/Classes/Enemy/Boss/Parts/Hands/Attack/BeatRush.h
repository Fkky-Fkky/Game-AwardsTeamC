/**
* @file BeatRush.h
* @brief �A���@�����U�������N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief BeatRush�N���X��`
	*/
	class BeatRush : public BossAction {
	public:
		BeatRush() {
			action_state_ = HAND_CHECK;
			r_beat_time_ = 0.0f;
			l_beat_time_ = 0.0f;
			l_move_dest_x_ = 0.0f;
			time_delta_ = 0.0f;
			wait_time_ = 0.0f;
			r_move_dest_x_ = 0.0f;
			r_hand_up_flag_ = false;
			l_hand_up_flag_ = false;
			is_r_attack_end_ = false;
			is_l_attack_end_ = false;
			is_r_return_end_ = false;
			is_l_return_end_ = false;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck();
		void Ready();
		void Attack(ActionManager* const act_m);
		void BeatR(ActionManager* const act_m);
		void BeatL(ActionManager* const act_m);
		void Reset();
		void HandReturn();

		int action_state_; /**< ���݂̍U���s���i�[ */

		float r_beat_time_; /**< �E��̍U�����Ԋi�[ */
		float l_beat_time_; /**< ����̍U�����Ԋi�[ */
		float r_move_dest_x_; /**< �E��̈ړ���i�[ */
		float l_move_dest_x_; /**< ����̈ړ���i�[ */
		float time_delta_; /**< ���� */
		float wait_time_; /**< �ҋ@���� */

		bool r_hand_up_flag_; /**< �E�����ɂ����邩 */
		bool l_hand_up_flag_; /**< �������ɂ����邩 */
		bool is_r_attack_end_; /**< �E��̍U�����I�������� */
		bool is_l_attack_end_; /**< ����̍U�����I�������� */
		bool is_r_return_end_; /**< �E�肪�������W�Ɉړ������� */
		bool is_l_return_end_; /**< ���肪�������W�Ɉړ������� */

		SimpleMath::Vector3 r_pos_; /**< �E��̍��W�i�[ */
		SimpleMath::Vector3 r_rote_; /**< �E��̉�]�i�[ */
		SimpleMath::Vector3 l_pos_; /**< ����̍��W�i�[ */
		SimpleMath::Vector3 l_rote_; /**< ����̉�]�i�[ */

		const float R_START_POS_X_ = -15.0f; /**< �E��̍\����ʒu */
		const float L_START_POS_X_ = -10.0f; /**< ����̍\����ʒu */

		const float WAIT_TIME_MAX_ = 0.5f; /**< �ҋ@���� */
		const float BEAT_L_START_TIME_ = 0.5f; /**< ���肪�U�����n�߂鎞�� */
		const float ADD_DISTANCE_ = 13.0f; /**< �ړ���ɒǉ�����X���W */
	};
}