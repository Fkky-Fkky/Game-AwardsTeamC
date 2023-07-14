/**
* @file Wait.h
* @brief �ҋ@�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"

namespace boss {
	/**
	* @brief Wait�N���X��`
	*/
	class Wait : public BossAction {
	public:
		Wait() {
			wait_time_ = 0.0f;
			max_wait_time_ = 0.0f;
			first_processed_flag_ = false;
		}
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m);

	private:
		float wait_time_; /**< �ҋ@���Ԋi�[ */
		float max_wait_time_; /**< �ő�ҋ@���Ԋi�[ */
		bool first_processed_flag_; /**< ��x������������t���O */
		const float HP_NORMAL_MAX_ = 30.0f; /**< HP3/3�ő�l */
		const float HP_NORMAL_MIN_ = 20.0f; /**< HP3/3�ŏ��l */
		const float HP_HARD_MIN_ = 10.0f; /**< HP2/3�ŏ��l */
		const float MAX_WAIT_TIME_NORMAL_ = 1.0f; /**< HP3/3���̑ҋ@���� */
		const float MAX_WAIT_TIME_HARD_ = 0.7f; /**< HP2/3���̑ҋ@���� */
		const float MAX_WAIT_TIME_VERY_HARD_ = 0.5f; /**< HP1/3���̑ҋ@���� */
	};
}