/**
* @file Boss.h
* @brief �{�X�̃X�e�[�^�X����������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace boss {
	/**
	* @brief Status�N���X��`
	*/
	class Status {
	public:
		Status() {
			damage_type_ = HAND;
			weak_count_ = 0;
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			weak_time_ = 0.0f;
			is_set_weak_time_ = false;
		};

		void Initialize();
		void Update(const float deltaTime, const ObjectManager* const obj_m);

		/**
		* @brief �{�X��HP�擾
		* 
		* @return �{�X��HP
		*/
		float GetBossHP() const { return hp_; }

		/**
		* @brief �E�B�[�N��Ԏ擾
		* 
		* @retval TRUE �E�B�[�N���
		* @retval FALSE �E�B�[�N��Ԃł͂Ȃ�
		*/
		bool IsWeak() const { return weak_count_ >= WEAK_COUNT_MAX_; }
	private:
		void DamageProcess();

		int damage_type_; /**< �_���[�W�̎�ނ��i�[ */
		int weak_count_; /**< �U�����ꂽ�� */
		float hp_; /**< �{�X��HP */
		float invincible_time_; /**< ���G���� */
		float weak_time_; /**< �E�B�[�N��Ԃ̎��� */
		bool is_set_weak_time_; /**< �E�B�[�N��Ԃ̎��Ԃ�ݒ肵���� */
		const int WEAK_COUNT_MAX_ = 3; /**< �E�B�[�N��ԂɂȂ�܂ł̉� */
		const float BOSS_HP_MAX_ = 30.0f; /**< �{�X�̍ő�HP */
		const float HAND_DAMAGE_ = 1.0f; /**< �肪�U�����󂯂����̃_���[�W�� */
		const float BODY_DAMAGE_ = 5.0f; /**< �{�̂��U�����󂯂����̃_���[�W�� */
		const float INVINCIBLE_TIME_MAX_ = 2.0f; /**< ���G���Ԃ̍ő�l */
		const float WEAK_TIME_MAX_ = 5.0f; /**< �E�B�[�N���Ԃ̍ő�l */

		/**
		* �󂯂�_���[�W�̃^�C�v 
		*/
		enum DAMAGE_TYPE_ {
			HAND, /**< �� */
			BODY /**< �{�� */
		};
	};
}