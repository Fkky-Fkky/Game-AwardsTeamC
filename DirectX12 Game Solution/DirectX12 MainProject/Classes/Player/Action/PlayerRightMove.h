/**
* @file PlayerRightMove.h
* @brief �v���C���[�E�ړ������N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerRightMove�N���X��`
	*/
	class PlayerRightMove : public PlayerActionState {
	public:
		PlayerRightMove() {};
		~PlayerRightMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);
	};
}