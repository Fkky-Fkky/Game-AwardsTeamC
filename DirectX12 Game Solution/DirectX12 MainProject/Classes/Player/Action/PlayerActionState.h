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
class PlayerActionManager;

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
		* 
		* @param[in] deltaTime ����
		* @param[out] player �v���C���[
		* @param[out] act_m �A�N�V�����}�l�[�W���[
		*/
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m) = 0;

	protected:
		const float PLAYER_MOVE_SPEED_ = 10.0f; /**< �ړ����x */
		const float FALL_SPEED_ = 15.0f; /**< �������x */
		const float PLAYER_ROTATION_ANGLE_ = 90.0f; /**< �����p�x */
		const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f; /**< �ő�ړ��\X���W */
		const float PLAYER_LIMIT_MIN_POS_X_ = -17.0f; /**< �ŏ��ړ��\X���W */
	};
}