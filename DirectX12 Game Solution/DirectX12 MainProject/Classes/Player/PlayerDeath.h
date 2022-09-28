/**
* @file PlayerDeath.h
* @brief �v���C���[���S�����N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerDeath�N���X��`
	*/
	class PlayerDeath : public PlayerActionState {
	public:
		PlayerDeath() {
			is_player_death_ = false;
		};
		~PlayerDeath() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);
		
		/**
		* @brief �v���C���[�����S���Ă��邩
		* 
		* @retval TRUE ���S���Ă���
		* @retval FALSE ���S���Ă��Ȃ�
		*/
		bool IsPlayerDeath()const { return is_player_death_; }

	private:
		bool is_player_death_; /**< �v���C���[�����S���Ă���*/

		const float DEATH_POS_Y_ = 0.1f; /**< ���S����Y���W */
	};
}