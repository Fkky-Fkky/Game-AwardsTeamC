/**
* @file PlayerLeftMove.h
* @brief �v���C���[���ړ������N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerLeftMove�N���X��`
	*/
	class PlayerLeftMove : public PlayerActionState {
	public:
		PlayerLeftMove() {};
		~PlayerLeftMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}