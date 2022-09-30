/**
* @file PlayerActionManager.h
* @brief �v���C���[�s�������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/Action/PlayerRightMove.h"
#include "Classes/Player/Action/PlayerLeftMove.h"
#include "Classes/Player/Action/PlayerJump.h"
#include "Classes/Player/Action/PlayerAttack.h"
#include "Classes/Player/Action/PlayerWait.h"
#include "Classes/Player/Action/PlayerActionState.h"
#include "Classes/Player/Action/PlayerDamage.h"
#include "Classes/Player/Action/PlayerDeath.h"

using namespace DirectX;

class ObjectManager;
class Player;

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
* @brief PlayerActionManager�N���X��`
*/
class PlayerActionManager {
public:
	PlayerActionManager() {
		player_action_state_ = PLAYER_STATE::WAIT;
		action_ = nullptr;
		is_switch_state_death_ = false;
	}
	~PlayerActionManager() {};

	void Initialize();
	void Update(const float deltaTime, Player* const player, const ObjectManager* const obj_m);

	void SwitchState(const PLAYER_STATE state, Player* const player);

	/**
	* @brief �v���C���[�̍U�����n�܂�����
	*
	* @retval TRUE �n�܂��Ă���
	* @retval FALSE �n�܂��Ă��Ȃ�
	*/
	bool IsPlayerAttackStart() const { return attack_.IsPlayerAttackStart(); }

	/**
	* @brief �v���C���[�����G��
	*
	* @retval TRUE ���G
	* @retval FALSE ���G�ł͂Ȃ�
	*/
	bool IsPlayerInvincible()  const { return dmg_.IsInvincible(); }

	/**
	* @brief �v���C���[�����S���Ă��邩
	*
	* @retval TRUE ���S���Ă���
	* @retval FALSE ���S���Ă��Ȃ�
	*/
	bool IsPlayerDeath() const { return death_.IsPlayerDeath(); }

private:
	int ConvertToMotion(const PLAYER_STATE player_state)const;

	bool is_switch_state_death_; /**< ���S��Ԃɐ؂�ւ����� */
	PLAYER_STATE player_action_state_; /**< ���݂̃v���C���[�s�� */

	/**
	* @brief �v���C���[���[�V�������
	*/
	enum PLAYER_MOTION {
		WAIT, /**< �ҋ@ */
		ATTACK, /**< �U�� */
		MOVE, /**< �ړ� */
		JUMP, /**< �W�����v */
		DAMAGE, /**< �_���[�W */
		DEATH /**< ���S */
	};

	player::PlayerRightMove      right_move_; /**< �v���C���[�E�ړ��N���X */
	player::PlayerLeftMove		 left_move_; /**< �v���C���[���ړ��N���X */
	player::PlayerJump           jump_; /**< �v���C���[�W�����v�N���X */
	player::PlayerAttack		 attack_; /**< �v���C���[�U���N���X */
	player::PlayerWait			 wait_; /**< �v���C���[�ҋ@�N���X */
	player::PlayerDamage		 dmg_; /**< �v���C���[�_���[�W�N���X */
	player::PlayerDeath			 death_; /**< �v���C���[���S�N���X */
	player::PlayerActionState*   action_; /**< �v���C���[��ԃN���X */
};