/**
* @file PlayerStatus.h
* @brief �v���C���[��HP�����N���X
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace player {
	/**
	* @brief PlayerState�N���X��`
	*/
	class PlayerStatus {
	public:
		PlayerStatus() {
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			damage_ = 0.0f;
			is_invincible_ = false;
		};
		~PlayerStatus() {};

		void Initialize();
		void Update(const float deltatime, const ObjectManager* const obj_m);

		/**
		* @brief �v���C���[��HP�擾
		* 
		* @return HP
		*/
		float GetPlayerHP() const { return hp_; }
	private:
		void DamageProcess();
		
		float hp_; /**< HP�i�[ */
		float invincible_time_; /**< ���G���Ԋi�[ */
		float damage_; /**< �_���[�W�ʊi�[ */
		bool is_invincible_; /**< ���G�� */

		const float PLAYER_HP_MAX_ = 30.0f; /**< HP�ő�l */
		const float INVINCIBLE_TIME_MAX_ = 1.5f; /**< ���G���� */
		const float OPEN_DAMAGE_ = 2.0f; /**< �{�X�̎肪�J���Ă���ꍇ�̃_���[�W�� */
		const float CLOSE_DAMAGE_ = 4.0f; /**< �{�X�̎肪�����Ă���ꍇ�̃_���[�W�� */
	};
}