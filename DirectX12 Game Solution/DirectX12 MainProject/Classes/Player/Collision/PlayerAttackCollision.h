/**
* @file PlayerAttackCollision.h
* @brief �v���C���[�U���R���W���������N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class Player;

namespace player {
	/**
	* @brief PayerAttackCollision�N���X��`
	*/
	class PlayerAttackCollision {
	public:
		PlayerAttackCollision() {
			attack_time_ = 0.0f;
			is_player_attack_ = false;
			is_effect_play_ = false;
			is_se_play_ = false;
		}
		~PlayerAttackCollision() {};

		void Initialize();
		void LoadAssets(DX9::SkinnedModel* const model_);
		void Update(const float deltaTime, const DX9::SkinnedModel* const model_, const Player* const player);

		/**
		* @brief �v���C���[�͍U�����Ă��邩
		* 
		* @retval TRUE ���Ă���
		* @retval FALSE ���Ă��Ȃ�
		*/
		bool IsPlayerAttack() const { return is_player_attack_; }

		/**
		* @brief �v���C���[�̍U���R���W�����擾
		* 
		* @return �U���R���W����
		*/
		BoundingOrientedBox GetAttackCollision() const { return collision_; }
	private:
		void AtkProcess(const Player* const player);
		BoundingOrientedBox collision_;
		float attack_time_; /**< �U�����鎞�Ԋi�[ */
		bool is_player_attack_; /**< �U�������Ă��邩 */
		bool is_effect_play_; /**< �G�t�F�N�g���Đ������� */
		bool is_se_play_; /**< SE���Đ������� */

		const float PLAYER_RIGHT_ = -90.0f; /**< �v���C���[�E���� */
		const float RIGHT_ANGLE_ = 0.0f; /**< �G�t�F�N�g�̉E���� */
		const float LEFT_ANGLE_ = 200.0f; /**< �G�t�F�N�g�̍����� */
		const float MAX_ATTACK_TIME_ = 3.3f; /**< �ő�U������ */
		const float ATTACK_DISTANCE_X_ = 4.5f; /**< �U���R���W������X���W */
		const float ATTACK_DISTANCE_Y_ = 1.5f; /**< �U���R���W������Y���W */
		const float ATTACK_START_TIME_ = 1.3f; /**< �U�����n�߂鎞�� */
		const float ATTACK_END_TIME_ = 1.7f; /**< �U�����I��点�鎞�� */
		const float COLLISION_SIZE_MULTIPLY_X_ = 0.1f; /**< �R���W������X�T�C�Y */
		const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f; /**< �R���W������Y�T�C�Y */
		const float COLLISION_SIZE_MULTIPLY_Z_ = 4.0f; /**< �R���W������Z�T�C�Y */
	};
}