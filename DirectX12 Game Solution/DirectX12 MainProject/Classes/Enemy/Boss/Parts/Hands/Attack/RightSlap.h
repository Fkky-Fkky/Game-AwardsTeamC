/**
* @file LeftSlap.h
* @brief ���ガ�����U�������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief RightSlap�N���X��`
	*/
	class RightSlap : public BossAction {
	public:
		RightSlap() {
			action_state_ = HAND_CHECK;
			time_delta_ = 0.0f;
			wait_time_  = 0.0f;
			hand_state_ = false;
			pos_ = SimpleMath::Vector3::Zero;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		void HandCheck(const ObjectManager* const obj_m);
		void Ready(ActionManager* const act_m);
		void Wait(ActionManager* const act_m);
		void RightSlapAttack(ActionManager* const act_m);
		void Reset();
		void HandReturn();

		int action_state_; /**< ���݂̍U���s���i�[ */

		float time_delta_; /**< ���Ԋi�[ */
		float wait_time_; /**< �ҋ@���Ԋi�[ */

		bool hand_state_; /**< ��̏�Ԋi�[ */

		SimpleMath::Vector3 pos_; /**< ��̍��W�i�[ */
	};
}