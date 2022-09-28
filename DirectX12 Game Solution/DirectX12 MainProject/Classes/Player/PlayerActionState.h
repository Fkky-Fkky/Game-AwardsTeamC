/**
* @file PlayerActionState.h
* @brief �v���C���[�s�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Player;

namespace player {
	/**
	* @brief PlayerActionState�N���X��`
	*/
	class PlayerActionState {
	public:
		/**
		* @brief �l�̏������������z�֐�
		*/
		virtual void Initialize() = 0;

		/**
		* @brief �l�̍X�V�������z�֐�
		*/
		virtual void Update(const float deltaTime, Player* const player) = 0;

	protected:
		const float PLAYER_MOVE_SPEED_ = 10.0f; /**< �ړ����x */
		const float FALL_SPEED_ = 15.0f; /**< �������x */
		const float PLAYER_ROTATION_ANGLE_ = 90.0f; /**< �����p�x */
		const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f; /**< �ő�ړ��\X���W */
		const float PLAYER_LIMIT_MIN_POS_X_ = -17.0f; /**< �ŏ��ړ��\X���W */
	};
}