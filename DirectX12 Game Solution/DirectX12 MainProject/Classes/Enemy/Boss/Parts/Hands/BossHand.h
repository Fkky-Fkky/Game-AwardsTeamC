/**
* @file BossHand.h
* @brief �{�X�̎���N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

/**
* @brief BossHand�N���X��`
*/
class BossHand : public BossParts{
public:
	BossHand() {
		motion_track_ = 0;
		timde_delta_  = 0.0f;
		motion_time_  = 0.0f;
		motion_time_max_  = 0.0f;
		motion_stop_time_ = 0.0f;
		motion_flag_	 = false;
		attack_flag_	 = false;
		is_death_motion_ = false;
	}

	~BossHand() {};
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);

	void PlayDeathMotion();
	/**
	* @brief ���W�̐ݒ�
	* 
	* @param[in] position ���W
	*/
	void SetHandPos(const SimpleMath::Vector3 position) { position_ = position; }

	/**
	* @brief ��]�̐ݒ�
	* 
	* @param[in] rotation ��]
	*/
	void SetHandRote(const SimpleMath::Vector3 rotation) { rotation_ = rotation; }

	/**
	* @brief �U���t���O�̐ݒ�
	* 
	* @param[in] attack_flag �U�����邩
	*/
	void SetAttackFlag(const bool attack_flag) { attack_flag_ = attack_flag; }

	void SetHandMotion(const int hand_motion);

	/**
	* @brief �U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsAttack() const { return attack_flag_; }

	/**
	* @brief ��̃R���W�����擾
	* 
	* @return ��̃R���W����
	*/
	BoundingOrientedBox GetHandCollision() const { return collision_; }

	/**
	* @brief ��̍��W�擾
	* 
	* @return ��̍��W
	*/
	SimpleMath::Vector3 GetHandPos() const { return position_; }

	/**
	* @brief ��̉�]�擾
	* 
	* @return ��̉�]
	*/
	SimpleMath::Vector3 GetRotation() const { return rotation_; }

private:
	void MotionStart();
	void MotionReset();
	void PlayMotion();
	void HandMotionAttack();
	void HandMotionWait()const;

	/**
	* @brief ��̃��[�V����
	*/
	enum HAND_MOTION {
		WAIT, /**< �ҋ@ */
		PAPER, /**< ����J�� */
		PAPER_BACK, /**< �J������Ԃ���ҋ@�ɖ߂� */
		ROCK, /**< ������� */
		ROCK_BACK /**< �����Ԃ���ҋ@�ɖ߂� */
	};

	int motion_track_; /**< ���[�V�����̃g���b�N���i�[ */
	float motion_time_; /**< ���[�V�����̍Đ����� */
	float motion_time_max_; /**< ���[�V�����̍ő�Đ����� */
	float timde_delta_; /**< ���� */
	float motion_stop_time_; /**< ���[�V�������~�߂鎞�� */
	bool motion_flag_; /**< ���[�V�������Đ�������t���O */
	bool attack_flag_; /**< �U�������Ă��邩 */
	bool is_death_motion_; /**< ���S���̃��[�V�������Đ����Ă��邩 */

	const int MOTION_MAX_  = 5; /**< ���[�V�����̎�ލő�l */
	const float BACK_MOTION_TIME_ = 0.96f; /**< �ҋ@��Ԃɖ߂郂�[�V�����̎��� */
	const float ATK_MOTION_TIME_  = 0.96f; /**< �J�������鎞�̃��[�V�����̎��� */
	const float COLLSION_SIZE_X_ = 1.7f; /**< �R���W������X�T�C�Y */
	const float COLLSION_SIZE_Y_ = 0.6f; /**< �R���W������Y�T�C�Y */
	const float COLLSION_SIZE_Z_ = 2.0f; /**< �R���W������Z�T�C�Y */
	const float HAND_SCALE = 0.8f; /**< ��̃��f���̑傫�� */
	const float STOP_TIME_ = 0.5f; /**< ���[�V�������~�߂鎞�� */
protected:

	BoundingOrientedBox collision_; /**< �R���W�������i�[ */

	const float INITIAL_POS_Y_ = 50.0f; /**< ��̏���X���W */
	const float INITIAL_POS_Z_ = 10.0f; /**< ��̏���Z���W */
	const float INITIAL_ROT_X_ = 30.0f; /**< ��̏�����]X�� */
	const float INITIAL_ROT_Y_ = 90.0f; /**< ��̏�����]Y�� */
};