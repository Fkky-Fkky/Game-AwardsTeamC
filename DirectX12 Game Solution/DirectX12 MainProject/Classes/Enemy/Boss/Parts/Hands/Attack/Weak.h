/**
* @file Weak.h
* @brief �E�B�[�N�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Weak�N���X��`
	*/
	class Weak : public BossAction {
	public:
		Weak() {
			weak_state_ = ATK_CANCEL;
			time_delta_ = 0.0f;
			weak_time_y_ = 0.0f;
			weak_y_ = 0.0f;
			pos_r_ = SimpleMath::Vector3::Zero;
			pos_l_ = SimpleMath::Vector3::Zero;
			rot_r_ = SimpleMath::Vector3::Zero;
			rot_l_ = SimpleMath::Vector3::Zero;
		}
		~Weak() {};
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void AtkCancel(ActionManager* const act_m);
		void WeakAction(ActionManager* const act_m);
		void WeakR();
		void WeakL();
		void Wait(const ObjectManager* const obj_m, ActionManager* const act_m);
		void InitialPosMove();

		int weak_state_; /**< ���݂̍s���i�[ */

		float time_delta_; /**< ���Ԋi�[ */
		float weak_time_y_; /**< �肪��Ԏ��̎��Ԋi�[ */
		float weak_y_; /**< �肪��ԏ����i�[ */

		SimpleMath::Vector3 pos_r_; /**< �E��̍��W�i�[ */
		SimpleMath::Vector3 pos_l_; /**< ����̍��W�i�[ */
		SimpleMath::Vector3 rot_r_; /**< �E��̉�]�i�[ */
		SimpleMath::Vector3 rot_l_; /**< ����̉�]�i�[ */

		const float WEAK_ROT_X_ = 150.0f; /**< �E�B�[�N��Ԏ��̉�]X�� */
		const float WEAK_POS_X_ = 18.0f; /**< �E�B�[�N��Ԏ���X���W */
		const float WEAK_POS_Y_ = 3.0f; /**< �E�B�[�N��Ԏ���Y���W */
		const float WEAK_SPEED_Y_ = 2.0f; /**< �肪��Ԏ��̎��� */
		const float WEAK_GRAVITY_ = 6.0f; /**< �肪��Ԏ��̏d�� */

		/**< �E�B�[�N��ԍs����� */
		enum WEAK_STATE {
			ATK_CANCEL, /**< �U���̃L�����Z�� */
			WEAK_ACTION, /**< �E�B�[�N */
			WAIT, /**< �ҋ@ */
			INITIAL_POS_MOVE, /**< �������W�ֈړ� */
			ACTION_END /**< �s���I�� */
		};
	};
}