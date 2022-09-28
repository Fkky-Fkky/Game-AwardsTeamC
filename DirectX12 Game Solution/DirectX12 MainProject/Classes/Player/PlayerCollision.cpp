#include "Classes/Player/PlayerCollision.h"

/**
* @brief �R���W�����̍쐬
* 
* @param[out] model �v���C���[���f��
*/
void player::PlayerCollision::LoadAssets(DX9::SkinnedModel* const model) {
    collision_ = model->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(   //�����蔻��̃T�C�Y����
        collision_.Extents.x * COLLISION_SIZE_MULTIPLY_X_,
        collision_.Extents.y * COLLISION_SIZE_MULTIPLY_Y_,
        collision_.Extents.z * COLLISION_SIZE_MULTIPLY_Z_
    );
}

/**
* @brief �R���W�����̍X�V
* 
* @param[in] model �v���C���[���f��
*/
void player::PlayerCollision::Update(const DX9::SkinnedModel* const model) {
    collision_.Center      = model->GetPosition() + SimpleMath::Vector3(0, CENTER_PLUS_Y_VALUE_, 0);
    collision_.Orientation = model->GetRotationQuaternion();
}