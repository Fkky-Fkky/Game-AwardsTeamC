/**
* @file PlayerCollision.h
* @brief �v���C���[�̃R���W���������N���X
* @outhor ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

namespace player {
	/**
	* @brief PlayerCollsion�N���X��`
	*/
	class PlayerCollision {
	public:
		PlayerCollision() {};
		~PlayerCollision() {};

		void LoadAssets(DX9::SkinnedModel* const model);
		void Update(const DX9::SkinnedModel* const model);

		/**
		* @brief �v���C���[�R���W�����̎擾
		* 
		* @return �R���W����
		*/
		BoundingOrientedBox GetColision() const { return collision_; }

	private:
		BoundingOrientedBox collision_; /**< �v���C���[�̃R���W�����i�[ */

		const float COLLISION_SIZE_MULTIPLY_X_ = 0.5f; /**< �R���W����X�T�C�Y */
		const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f; /**< �R���W����Y�T�C�Y */
		const float COLLISION_SIZE_MULTIPLY_Z_ = 0.5f; /**< �R���W����Z�T�C�Y */
		const float CENTER_PLUS_Y_VALUE_ = 2.0f; /**< �R���W������Y���W */
	};
}