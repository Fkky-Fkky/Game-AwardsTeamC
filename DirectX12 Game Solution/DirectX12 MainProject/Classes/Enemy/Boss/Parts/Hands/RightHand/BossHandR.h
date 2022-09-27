/**
* @file BossHandR.h
* @brief �{�X�̉E�菈���N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

namespace boss {
	/**
	* @brief BossHandR�N���X��`
	*/
	class BossHandR : public BossHand {
	public:
		void Initialize();
		void LoadAssets();
		virtual void Update(const float deltaTime);

	private:
		const float INITIAL_POS_X_ = -13.0f; /**< ����X���W */
		const float ADD_COLLISION_POS_X_ = -1.0f; /**< �R���W������X���W */
	};
}