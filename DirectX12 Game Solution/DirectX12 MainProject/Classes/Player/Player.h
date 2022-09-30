/**
* @file Player.h
* @brief �v���C���[�̏����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerCollision.h"
#include "Classes/Player/PlayerAttackCollision.h"
#include "Classes/Player/PlayerStatus.h"
#include "Classes/Player/Action/PlayerActionManager.h"

using namespace DirectX;

class ObjectManager;

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
		player_motion_track_ = 0;
		jump_motion_time_ = 0.0f;
		death_motion_time_ = 0.0f;
		is_jump_motion_play_ = false;
		is_death_motion_play_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
	}
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

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
	void SetMotion(const int player_motion);
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
	bool IsPlayerAttackStart() const { return action_.IsPlayerAttackStart(); }

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
	bool IsPlayerInvincible()  const { return action_.IsPlayerInvincible(); }

	/**
	* @brief �v���C���[�����S���Ă��邩
	* 
	* @retval TRUE ���S���Ă���
	* @retval FALSE ���S���Ă��Ȃ�
	*/
	bool IsPlayerDeath() const { return action_.IsPlayerDeath(); }

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

	DX9::SKINNEDMODEL model_; /**< �v���C���[���f���i�[ */

	XAudio::SOUNDEFFECT atk_se_; /**< �U��SE�i�[ */

	int player_motion_track_; /**< ���[�V�����g���b�N�i�[ */
	float jump_motion_time_; /**< �W�����v���[�V�����̍Đ����� */
	float death_motion_time_; /**< ���S���[�V�����̍Đ����� */

	bool is_jump_motion_play_; /**< �W�����v���[�V�����Đ����邩 */
	bool is_death_motion_play_; /**< ���S���[�V�����Đ����邩 */

	SimpleMath::Vector3 pos_; /**< �v���C���[�̍��W�i�[ */
	SimpleMath::Vector3 rot_; /**< �v���C���[�̉�]�i�[ */

	const int MOTION_MAX_ = 6; /**< ���[�V�����̍ő吔 */
	const float PLAYER_SCALE_ = 0.02f; /**< �v���C���[���f���̑傫�� */
	const float RIGHT_WARD_ = -90.0f; /**< �E���� */

	player::PlayerCollision       player_colision_; /**< �v���C���[�R���W�����N���X */
	player::PlayerAttackCollision player_attack_colision_; /**< �v���C���[�U���R���W�����N���X */
	player::PlayerStatus		 player_status_; /**< �v���C���[�X�e�[�^�X�N���X */
	PlayerActionManager action_; /**< �v���C���[�A�N�V�����}�l�[�W���[�N���X */
};