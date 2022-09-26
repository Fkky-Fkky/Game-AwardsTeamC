/**
* @file Death.h
* @brief �{�X���S���̎�̏���
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Death�N���X��`
	*/
	class Death : public BossAction {
	public:
		Death() {
			death_state_ = ATK_CANCEL;
			time_delta_ = 0.0f;
			death_jump_time_ = 0.0f;
			death_jump_y_ = 0.0f;
			l_pos_ = SimpleMath::Vector3::Zero;
			r_pos_ = SimpleMath::Vector3::Zero;
			l_rot_ = SimpleMath::Vector3::Zero;
			r_rot_ = SimpleMath::Vector3::Zero;
		};
		~Death() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void AtkCancel(ActionManager* const act_m);
		void DeathAction(ActionManager* const act_m);

		int death_state_; /**< ���݂̍s���i�[ */
		float time_delta_; /**< ����*/
		float death_jump_time_; /**< �肪��Ԏ��� */
		float death_jump_y_; /**< �肪��ԏ����i�[ */

		SimpleMath::Vector3 l_pos_; /**< ����̍��W�i�[ */
		SimpleMath::Vector3 r_pos_; /**< �E��̍��W�i�[ */
		SimpleMath::Vector3 l_rot_; /**< ����̉�]�i�[ */
		SimpleMath::Vector3 r_rot_; /**< �E��̉�]�i�[ */

		const float DEATH_JUMP_SPEED_Y_ = 2.0f; /**< �肪��ԃX�s�[�h */
		const float DEATH_JUMP_GRAVITY_ = 6.0f; /**< �肪��ԂƂ��̏d�� */
		const float DEATH_ROT_X_ = 150.0f; /**< ���S���̉�]X�� */
		const float DEATH_POS_X_ = 18.0f; /**< ���S����X���W */
		const float DEATH_POS_Y_ = 2.5f; /**< ���S����Y���W */

		/**< ���S���̍s����� */
		enum DEATH_STATE_ {
			ATK_CANCEL, /**< �U�����I�� */
			DEATH_ACTION, /**< ���S���̍s�� */
			ACTION_END /**< �s���I�� */
		};
	};
}