/**
* @file PlayerJump.h
* @brief �v���C���[�W�����v�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Player/Action/PlayerActionState.h"

namespace player {
	/**
	* @brief PlayerJump�N���X��`
	*/
	class PlayerJump : public PlayerActionState {
	public:
		PlayerJump() {
			action_state_ = READY;
			time_delta_ = 0.0f;
			jump_time_ = 0.0f;
			cool_time_ = 0.0f;
			player_up_flag_ = false;
			pos_ = SimpleMath::Vector3::Zero;
			rot_ = SimpleMath::Vector3::Zero;
			old_player_pos_ = SimpleMath::Vector3::Zero;
		}
		~PlayerJump() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player, PlayerActionManager* const act_m);

	private:
		void Ready();
		void Jump(Player* const player);
		void CoolTime();
		void JumpingMove();

		int action_state_; /**< ���ݍs���i�[ */

		float time_delta_; /**< ���� */
		float jump_time_; /**< �W�����v���Ԋi�[ */
		float cool_time_; /**< �N�[���^�C���i�[ */

		bool  player_up_flag_; /**< �v���C���[���㏸���Ă��邩 */

		SimpleMath::Vector3 pos_; /**< �v���C���[�̍��W�i�[ */
		SimpleMath::Vector3 rot_; /**< �v���C���[�̉�]�i�[ */
		SimpleMath::Vector3 old_player_pos_; /**< �ߋ��̃v���C���[�̍��W */

		/**< �W�����v�s���̎�� */
		enum ACTION_STATE_ {
			READY, /**< �\�� */
			JUMP, /**< �W�����v */
			COOL_TIME, /**< �N�[���^�C�� */
			ACTION_END /**< �s���̎�� */
		};

		const float GRAVITY_ = 20.0f; /**< �d�� */
		const float V0_ = 16.0f; /**< �W�����v�̏��� */
		const float HALF_ = 0.5f; /** 1/2 */
		const float DOWN_SPEED_ = 2.0f; /**< �������x */
		const float GROUND_Y_ = 0.0f; /**< ���n�n�_ */
		const float COOL_TIME_MAX_ = 0.6f; /**< �N�[���^�C�� */
		const float JUMPING_MOVE_SPEED_ = 5.0f; /**< �W�����v���̈ړ����x */
		const float JUMPING_MOVE_SPEED_REVERSE = 2.5f; /**< �W�����v���̔��]�ړ����x*/
	};
}