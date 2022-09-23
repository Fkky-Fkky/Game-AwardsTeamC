/**
* @file BossBody.h
* @brief �{�X�̖{�̂���������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class ObjectManager;
class Boss;

namespace boss {
	/**
	* @brief BossBody�N���X��`
	*/
	class BossBody : public BossParts {
	public:
		BossBody() {
			time_delta_		= 0.0f;
			shake_time_		= 0.0f;
			body_jump_y_	= 0.0f;
			body_jump_time_ = 0.0f;
			is_weak_		= false;
			is_shake_		= false;
			shake_set_flag_ = false;
			is_body_death_  = false;
			is_shake_reset_ = false;
			is_start_pos_	= false;
		}
		~BossBody() {};

		virtual void Initialize();
		void LoadAssets();
		void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);

		/**
		* @brief �{�X�{�̂�����ł��邩
		* 
		* @retval TRUE ����ł���
		* @retval FALSE ����ł��Ȃ�
		*/
		bool IsBodyDeath() const { return is_body_death_; }

		/**
		* @brief �{�X�{�̂̃R���W�����擾
		* 
		* @return �{�X�{�̂̃R���W����
		*/
		BoundingOrientedBox GetBodyCollision() const { return body_coll_; }
	private:
		void AdventAction();
		void WeakAction();
		void DeathAction();

		BoundingOrientedBox body_coll_; /**< �R���W�������i�[ */
		float time_delta_; /**< ���Ԃ��i�[ */
		float shake_time_; /**< ��ʂ�h�炷���Ԋi�[ */
		float body_jump_y_; /**< ��Ԏ��̐��l�i�[ */
		float body_jump_time_; /**< ��Ԏ��� */
		bool is_weak_; /**< �E�B�[�N��Ԃ� */
		bool is_shake_; /**< ��ʂ��h��Ă��邩 */
		bool shake_set_flag_; /**< ��ʗh���ݒ肵���� */
		bool is_body_death_; /**< �{�̂�����ł��邩 */
		bool is_shake_reset_; /**< ��ʗh������Z�b�g������ */
		bool is_start_pos_; /**< �X�^�[�g�ʒu�ɂ��邩 */

		const float BODY_INIT_POS_Y_  = 50.0f; /**< ����Y���W */
		const float BODY_INIT_POS_Z_  = 15.0f; /**< ����Z���W */
		const float BODY_INIT_ROT_X_  = -20.0f; /**< ������]X�� */
		const float BODY_START_POS_Y_ = 17.0f; /**< �X�^�[�g�ʒu */
		const float BODY_WEAK_POS_Y_  = 5.0f; /**< �E�B�[�N��Ԏ���Y���W */
		const float BODY_WEAK_POS_Z_  = 5.0f; /**< �E�B�[�N��Ԏ���Z���W */
		const float BODY_DEATH_POS_Y_ = 4.0f; /**< ���S����Z���W */
		const float DEATH_ROTATION_X_ = 40.0f; /**< ���S���̉�]X�� */
		const float BODY_SCALE_ = 0.8f; /**< ���f���̑傫�� */
		const float COLLISION_SIZE_X_ = 0.1f; /**< �����蔻���X�T�C�Y */
		const float COLLISION_SIZE_Z_ = 0.8f; /**< �����蔻���Z�T�C�Y */
		const float ADVENT_SPEED_	 = 10.0f; /**< �o�ꎞ�̍~��Ă���X�s�[�h */
		const float BODY_UP_SPEED_Y_ = 10.0f; /**< ��Ɉړ�����X�s�[�h */
		const float MOVE_SPEED_Z_	 = 20.0f; /**< Z���W�œ����X�s�[�h */
		const float JUMP_SPEED_		 = 1.0f; /**< ��ԂƂ��̏��� */
		const float ROTATION_SPEED_  = 10.0f; /**< ��]����X�s�[�h */
		const float DEATH_ROTATION_SPEED_ = 80.0f; /**< ���S���̉�]����X�s�[�h */
		const float SHAKE_TIME_MAX_ = 0.2f; /**< ��ʗh�ꂷ�鎞�� */
		const float HALF_		= 0.5f; /**< ���� */
		const float GRAVITY_	= 2.0f; /**< �d�� */
	};
}