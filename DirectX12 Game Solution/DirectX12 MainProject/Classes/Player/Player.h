/**
* @file Player.h
* @brief �v���C���[�̏����N���X
* @author ���㏃��
*/

#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerRightMove.h"
#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerAttack.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"
#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/PlayerActionState.h"
#include "Classes/Player/PlayerDamage.h"
#include "Classes/Player/PlayerDeath.h"
#include "Classes/Player/PlayerStatus.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief �v���C���[�̏�Ԏ��
*/
enum class PLAYER_STATE {
	WAIT, /**< �ҋ@ */
	RIGHT_MOVE, /**< �E�ړ� */
	LEFT_MOVE, /**< ���ړ� */
	JUMP, /**< �W�����v */
	ATTACK, /**< �U�� */
	DAMAGE, /**< �_���[�W */
	DEATH /**< ���S */
};

/**
* @brief �v���C���[���[�V�������
*/
enum class PLAYER_MOTION {
	WAIT, /**< �ҋ@ */
	ATTACK, /**< �U�� */
	MOVE, /**< �ړ� */
	JUMP, /**< �W�����v */
	DAMAGE, /**< �_���[�W */
	DEATH /**< ���S */
};

/**
* @brief Player�N���X��`
*/
class Player {
public:
	Player() {
		player_action_state_ = PLAYER_STATE::WAIT;
		player_motion_track_ = 0;
		player_action_ = nullptr;
		jump_motion_time_ = 0.0f;
		death_motion_time_ = 0.0f;
		is_jump_motion_play_ = false;
		is_death_motion_play_ = false;
		is_switch_state_death_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
	}
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void SwitchState(const PLAYER_STATE state);
	/**
	* @brief ���W�ݒ�
	* 
	* @param[in] position ���W
	*/
	void SetPlayerPosition(const SimpleMath::Vector3 position) { pos_ = position; }

	/**
	* @brief ��]�ݒ�
	* 
	* @param[in] rotation ��]
	*/
	void SetPlayerRotation(const SimpleMath::Vector3 rotation) { rot_ = rotation; }
	void SetMotion(const PLAYER_MOTION player_motion);
	void PlayAtkSE()const;

	/**
	* @biref �v���C���[��HP�擾
	* 
	* @return �v���C���[��HP
	*/
	float GetPlayerHP() const { return player_status_.GetPlayerHP(); }

	/**
	* @brief �v���C���[�̍U�����n�܂�����
	* 
	* @retval TRUE �n�܂��Ă���
	* @retval FALSE �n�܂��Ă��Ȃ�
	*/
	bool IsPlayerAttackStart() const { return player_attack_.IsPlayerAttackStart(); }

	/**
	* @brief �v���C���[���U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsPlayerAttack() const { return player_attack_colision_.IsPlayerAttack(); }

	/**
	* @brief �v���C���[�����G��
	* 
	* @retval TRUE ���G
	* @retval FALSE ���G�ł͂Ȃ�
	*/
	bool IsPlayerInvincible()  const { return player_dmg_.IsInvincible(); }

	/**
	* @brief �v���C���[�����S���Ă��邩
	* 
	* @retval TRUE ���S���Ă���
	* @retval FALSE ���S���Ă��Ȃ�
	*/
	bool IsPlayerDeath() const { return player_death_.IsPlayerDeath(); }

	/**
	* @brief �v���C���[�̍��W�擾
	* 
	* @return �v���C���[�̍��W
	*/
	SimpleMath::Vector3 GetPlayerPosition() const { return pos_; }

	/**
	* @brief �v���C���[�̉�]�擾
	* 
	* @return �v���C���[�̉�]
	*/
	SimpleMath::Vector3 GetPlayerRotation() const { return rot_; }

	/**
	* @brief �v���C���[�̃R���W�����擾 
	* 
	* @return �v���C���[�̃R���W����
	*/
	BoundingOrientedBox GetPlayerCollision() const { return player_colision_.GetColision(); }

	/**
	* @brief �v���C���[�̍U���R���W�����擾
	* 
	* @return �v���C���[�̍U���R���W����
	*/
	BoundingOrientedBox GetPlayerAttackCollision() const { return player_attack_colision_.GetAttackCollision(); }

private:
	void ResetPlayerMotion()const;
	void JumpMotion(const float deltaTime);
	void DeathMotion(const float delaTime);
	PLAYER_MOTION ConvertToMotion(const PLAYER_STATE player_state)const;

	DX9::SKINNEDMODEL model_; /**< �v���C���[���f���i�[ */

	XAudio::SOUNDEFFECT atk_se_; /**< �U��SE�i�[ */

	PLAYER_STATE player_action_state_; /**< ���݂̃v���C���[�s�� */
	int player_motion_track_; /**< ���[�V�����g���b�N�i�[ */
	float jump_motion_time_; /**< �W�����v���[�V�����̍Đ����� */
	float death_motion_time_; /**< ���S���[�V�����̍Đ����� */

	bool is_jump_motion_play_; /**< �W�����v���[�V�����Đ����邩 */
	bool is_death_motion_play_; /**< ���S���[�V�����Đ����邩 */
	bool is_switch_state_death_; /**< ���S��Ԃɐ؂�ւ����� */

	SimpleMath::Vector3 pos_; /**< �v���C���[�̍��W�i�[ */
	SimpleMath::Vector3 rot_; /**< �v���C���[�̉�]�i�[ */

	const int MOTION_MAX_ = 6; /**< ���[�V�����̍ő吔 */
	const float PLAYER_SCALE_ = 0.02f; /**< �v���C���[���f���̑傫�� */
	const float RIGHT_WARD_ = -90.0f; /**< �E���� */

	player::PlayerRightMove      player_right_move_; /**< �v���C���[�E�ړ��N���X */
	player::PlayerLeftMove		 player_left_move_; /**< �v���C���[���ړ��N���X */
	player::PlayerJump           player_jump_; /**< �v���C���[�W�����v�N���X */
	player::PlayerAttack		 player_attack_; /**< �v���C���[�U���N���X */
	player::PlayerColision       player_colision_; /**< �v���C���[�R���W�����N���X */
	player::PlayerAttackColision player_attack_colision_; /**< �v���C���[�U���R���W�����N���X */
	player::PlayerWait			 player_wait_; /**< �v���C���[�ҋ@�N���X */
	player::PlayerDamage		 player_dmg_; /**< �v���C���[�_���[�W�N���X */
	player::PlayerDeath			 player_death_; /**< �v���C���[���S�N���X */
	player::PlayerActionState*	 player_action_; /**< �v���C���[��ԃN���X */
	player::PlayerStatus		 player_status_; /**< �v���C���[�X�e�[�^�X�N���X */
};