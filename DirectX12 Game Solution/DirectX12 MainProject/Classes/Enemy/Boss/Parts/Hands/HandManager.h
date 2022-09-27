/**
* @file HandManager.h
* @brief ����Ǘ�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include <random>

using namespace DirectX;

/**
* @brief HandManager�N���X��`
*/
class HandManager {
public:
	HandManager() {
		hand_state_		= ROCK;
		old_hand_state_ = PAPER;
		same_handstate_flag_   = false;
	}
	~HandManager() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render()const;

	void RandomHandState(const bool is_rush);

	/**
	* @brief ����J���Ă��邩
	* 
	* @retval TRUE ����J���Ă���
	* @retval FALSE ��������Ă���
	*/
	bool IsHandOpen() const { return hand_state_; }

	/**
	* @brief ���肪�U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsLHandAttack() const { return hand_l.IsAttack(); }

	/**
	* @brief �E�肪�U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsRHandAttack() const { return hand_r.IsAttack(); }

	/**
	* @brief ����擾
	* 
	* @return BossHandL
	*/
	boss::BossHandL& GetHandL() { return hand_l; }

	/**
	* @brief �E��擾
	* 
	* @return BossHandR
	*/
	boss::BossHandR& GetHandR() { return hand_r; }

	/**
	* @brief ����̃R���W�����擾
	* 
	* @return ����̃R���W����
	*/
	BoundingOrientedBox GetLHandCollision() const { return hand_l.GetHandCollision(); }

	/**
	* @brief �E��̃R���W�����擾
	* 
	* @return �E��̃R���W����
	*/
	BoundingOrientedBox GetRHandCollision() const { return hand_r.GetHandCollision(); }
private:
	boss::BossHandL hand_l; /**< �{�X����N���X */
	boss::BossHandR hand_r; /**< �{�X�E��N���X */

	std::mt19937 random_engine_; /**< �����_���G���W�� */
	std::uniform_int_distribution<int> random_hand_dist_; /**< ��̏�ԓ��ꕪ�z */

	bool hand_state_; /**< ��̏�Ԃ��i�[ */
	bool old_hand_state_; /**< �ЂƂO�̎�̏�Ԃ��i�[ */
	bool same_handstate_flag_; /** ��̏�Ԃ��O�Ɠ����� */

	/**< ��̏�� */
	enum HAND_STATE {
		ROCK, /** <��������Ă���(�O�[) */
		PAPER /** <����J���Ă���(�p�[) */
	};
};