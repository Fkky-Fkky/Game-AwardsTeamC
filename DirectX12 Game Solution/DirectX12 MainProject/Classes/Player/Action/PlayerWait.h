/**
* @file PlayerWait.h
* @brief �v���C���[�ҋ@�����N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerWait�N���X��`
	*/
	class PlayerWait : public PlayerActionState {
		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);
	};
}