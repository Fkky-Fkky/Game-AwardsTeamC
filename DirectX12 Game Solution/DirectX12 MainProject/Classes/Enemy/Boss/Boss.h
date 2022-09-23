/**
* @file Boss.h
* @brief �{�X�֘A�N���X���܂Ƃ߂ď�������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Enemy/Boss/Status.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief Boss�N���X��`
*/
class Boss {
public:
	Boss() {
		is_vertical_shake_ = false;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	/*
	* @brief �J�����c�h��t���O�ݒ�
	* 
	* @param[in] enable �J������h�炷��
	*/
	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	/**
	* @brief �{�X��HP�擾
	* 
	* @return �{�X��HP
	*/
	float GetBossHP() const { return status_.GetBossHP(); }

	/**
	* @brief �{�X�̃E�B�[�N��Ԏ擾
	* 
	* @retval TRUE �E�B�[�N���
	* @retval FALSE �E�B�[�N��Ԃł͂Ȃ�
	*/	
	bool IsBossWeak() const { return status_.IsWeak(); }

	/**
	* @brief �{�X������ł��邩
	* 
	* @retval TRUE ����ł���
	* @retval FALSE ����ł��Ȃ�
	*/
	bool IsBossDeath() const { return body_.IsBodyDeath() && action_.IsHandDeath(); }

	/**
	* @brief �J�������c�h�ꂳ���邩
	* 
	* @retval TRUE �h�炷
	* @retval FALSE �h�炳�Ȃ�
	*/
	bool IsVerticalShake() const { return action_.IsVerticalShake() || is_vertical_shake_; }

	/**
	* @brief �J���������h�ꂳ���邩
	*
	* @retval TRUE �h�炷
	* @retval FALSE �h�炳�Ȃ�
	*/
	bool IsSideShake() const { return action_.IsSideShake(); }

	/**
	* @brief �{�X�̎肪�J���Ă��邩
	*
	* @retval TRUE �J���Ă���
	* @retval FALSE �J���Ă��Ȃ�
	*/
	bool IsHandOpen() const { return action_.IsHandOpen(); }

	/**
	* @brief ���肪�U�����Ă��邩
	*
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsLHandAttack() const { return action_.IsLHandAttack(); }

	/**
	* @brief �E�肪�U�����Ă��邩
	*
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsRHandAttack() const { return action_.IsRHandAttack(); }

	/**
	* @brief ����̃R���W�����擾
	*
	* @return ����̃R���W����
	*/
	BoundingOrientedBox GetLHandCollision() const { return action_.GetLHandCollision(); }

	/**
	* @brief �E��̃R���W�����擾
	*
	* @return �E��̃R���W����
	*/
	BoundingOrientedBox GetRHandCollision() const { return action_.GetRHandCollision(); }

	/**
	* @brief �{�̂̃R���W�����擾
	*
	* @return �{�̂̃R���W����
	*/
	BoundingOrientedBox GetBodyCollision() const { return body_.GetBodyCollision(); }

private:
	boss::Status status_; /**< �X�e�[�^�X�N���X */
	boss::BossBody body_; /**< �{�f�B�[�N���X */
	ActionManager action_; /**< �A�N�V�����}�l�[�W���[�N���X */
	
	bool is_vertical_shake_; /**< �J�������c�h�ꂳ���邩 */
};