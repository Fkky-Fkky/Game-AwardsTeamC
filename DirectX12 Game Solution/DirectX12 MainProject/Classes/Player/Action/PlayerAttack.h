/**
* @file PlayerAttack.h
* @brief �v���C���[�U�������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerAttack�N���X��`
	*/
	class PlayerAttack : public PlayerActionState {
	public:
		PlayerAttack() {
			attack_time_ = 0.0f;
			attack_flg_ = false;
		};
		~PlayerAttack() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

		/**
		* @brief �v���C���[���U�����n�߂���
		* 
		* @retval TRUE �n�߂�
		* @ratval FALSE �n�߂Ă��Ȃ�
		*/
		bool IsPlayerAttackStart() const { return attack_flg_; }

	private:
		float attack_time_; /**< �U�����Ԋi�[ */
		bool attack_flg_; /**< �U���t���O */
		const float MAX_ATTACK_TIME_ = 3.3f; /**< �ő�U������ */
	};
}