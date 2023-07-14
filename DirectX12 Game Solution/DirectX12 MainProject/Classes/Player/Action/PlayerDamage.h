/**
* @file PlayerDamage.h
* @brief �v���C���[�_���[�W�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerDamage�N���X��`
	*/
	class PlayerDamage : public PlayerActionState {
	public:
		PlayerDamage() {
			dmg_time = 0.0f;
			knock_back_dest_ = 0.0f;
			one_process_flag_ = false;
			is_invinsible_ = false;
		}
		~PlayerDamage() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

		/**
		* @brief �v���C���[�����G��
		* 
		* @retval TRUE ���G
		* @retval FALSE ���G�ł͂Ȃ�
		*/
		bool IsInvincible() const { return is_invinsible_; }
	private:

		float dmg_time; /**< �_���[�W��Ԃ̎��Ԋi�[ */
		float knock_back_dest_; /**< �m�b�N�o�b�N�̈ړ��� */
		bool one_process_flag_; /**< ��x������������ */
		bool is_invinsible_; /**< ���G�� */

		SimpleMath::Vector3 pos_; /**< ���W�i�[ */
		SimpleMath::Vector3 rot_; /**< ��]�i�[ */
		const float ADD_DEST_ = 3.0f; /**< �ǉ�����ړ��� */
		const float KNOCK_BACK_SPEED_ = 20.0f; /**< �m�b�N�o�b�N���x */
		const float DMG_TIME_MAX_ = 0.6f; /**< �_���[�W��Ԃ̎��� */
	};
}