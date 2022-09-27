/**
* @file ActionManager.h
* @brief �{�X�̍U�����Ǘ�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"
#include <random>
#include "Base/DX12Effekseer.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief ActionManager��`
*/
class ActionManager {
public:
	ActionManager() {
		action_		 = nullptr;
		beat_effect_ = nullptr;
		attack_state_ = WAIT;
		boss_hp_	  = 0.0f;
		action_end_flag_	   = false;
		is_vertical_shake_	   = false;
		is_side_shake_		   = false;
		is_switch_state_weak_  = false;
		is_switch_state_death_ = false;
		is_hand_death_		   = false;
	}

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;

	void RandomAttackState();
	void ActionEnd();
	void DeathActionEnd();
	void PlaySlapSE()const;
	void PlayBeatSE()const;
	void PlayBeatEffect(const SimpleMath::Vector3 effect_pos)const;

	/**
	* @brief �J�����c�h��ݒ�
	* 
	* @param[in] eneable �J�������c�h�ꂳ���邩
	*/
	void SetVerticalShake(const bool enable) { is_vertical_shake_ = enable; }

	/**
	* @brief �J�������h��ݒ�
	* 
	* @param[in] enable �J���������h�ꂳ���邩
	*/
	void SetSideShake(const bool enable) { is_side_shake_ = enable; }
	
	/**
	* @brief �J�������c�h�ꂳ���邩
	* 
	* @retval TRUE �h�炷
	* @retval FALSE �h�炳�Ȃ�
	*/
	bool IsVerticalShake() const { return is_vertical_shake_; }

	/**
	* @brief �J���������h�ꂳ���邩
	* 
	* @retval TRUE �h�炷
	* @retval FALSE �h�炳�Ȃ�
	*/
	bool IsSideShake() const { return is_side_shake_; }

	/**
	* @brief �肪����ł��邩
	* 
	* @retval TRUE ����ł���
	* @retval FALSE ����ł��Ȃ�
	*/
	bool IsHandDeath() const { return is_hand_death_; }

	/**
	* @brief �肪�J���Ă��邩
	* 
	* @retval TRUE �J���Ă���(�p�[)
	* @retval FALSE �����Ă���(�O�[)
	*/
	bool IsHandOpen() const { return hand_.IsHandOpen(); }

	/**
	* @brief ���肪�U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsLHandAttack() const { return hand_.IsLHandAttack(); }

	/**
	* @brief �E�肪�U�����Ă��邩
	* 
	* @retval TRUE �U�����Ă���
	* @retval FALSE �U�����Ă��Ȃ�
	*/
	bool IsRHandAttack() const { return hand_.IsRHandAttack(); }

	/**
	* @brief ����̃R���W�����擾
	* 
	* @return ����̃R���W����
	*/
	BoundingOrientedBox GetLHandCollision() const { return hand_.GetLHandCollision(); }

	/**
	* @brief �E��̃R���W�����擾
	* 
	* @return �E��̃R���W����
	*/
	BoundingOrientedBox GetRHandCollision() const { return hand_.GetRHandCollision(); }
private:
	void SwitchStateAttack();
	void SwitchStateWait();
	void SwitchStateWeak();
	void SwitchStateDeath();

	boss::BossAction* action_; /**< �{�X�A�N�V�����N���X */
	HandManager hand_; /**< �n���h�}�l�[�W���[�N���X */

	EFFECT beat_effect_; /**< �@�����G�t�F�N�g�i�[ */
	std::mt19937 random_engine_; /**< �����_���G���W�� */
	std::uniform_int_distribution<int> random_atk_dist_; /**< �U���̎�ޓ��ꕪ�z */

	XAudio::SOUNDEFFECT slap_se_; /**< �ガ����SE�i�[ */
	XAudio::SOUNDEFFECT	beat_se_; /**< �@����SE�i�[ */

	int attack_state_; /**< �U���̎�ފi�[ */
	float boss_hp_; /**< �{�X��HP�i�[ */
	bool action_end_flag_; /**< �s���I���t���O */
	bool is_vertical_shake_; /**< �J�����c�h�ꂳ���邩 */
	bool is_side_shake_; /**< �J�������h�ꂳ���邩*/
	bool is_switch_state_weak_; /**< �E�B�[�N��Ԃɐ؂�ւ����� */
	bool is_switch_state_death_; /**< ���S��Ԃɐ؂�ւ����� */
	bool is_hand_death_; /**< �肪���S���Ă��邩 */

	const int ATTACK_STATE_MIN_ = 1; /**< �U���̎�ލŏ��l */
	const int ATTACK_STATE_MAX_ = 6; /**< �U���̎�ލő�l */
	const int NORMAL_MODE_MAX_ = 4; /**< �{�XHP3/3���U���̎�ލő�l */
	const int HARD_MODE_MAX_ = 5; /**< �{�X��HP2/3���U���̎�ލő�l */
	const float HP_NORMAL_MAX_ = 30.0f; /**< �{�X��HP3/3�ő�l */
	const float HP_NORMAL_MIN_ = 20.0f; /**< �{�X��HP3/3�ŏ��l */
	const float HP_HARD_MIN_ = 10.0f; /**< �{�X��HP2/3�ŏ��l */

	/**
	* @brief �{�X�̍s�����
	*/
	enum BOSS_STATE {
		WAIT, /**< �ҋ@��� */
		LEFT_BEAT, /**< ���@�����U�� */
		LEFT_SLAP, /**< ���ガ�����U�� */
		RIGHT_BEAT, /**< �E�@�����U�� */
		RIGHT_SLAP, /**< �E�ガ�����U�� */
		DOUBLE_SLAP, /**< ����ガ�����U�� */
		BEAT_RUSH_R /**< �A���@�����U�� */
	};
};