#include "Classes/Player/PlayerColision.h"

void player::PlayerColision::LoadAssets(DX9::SkinnedModel* const model) {
    collision_ = model->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(   //当たり判定のサイズ調整
        collision_.Extents.x * COLLISION_SIZE_MULTIPLY_X_,
        collision_.Extents.y * COLLISION_SIZE_MULTIPLY_Y_,
        collision_.Extents.z * COLLISION_SIZE_MULTIPLY_Z_
    );
}

void player::PlayerColision::Update(const float deltaTime, const DX9::SkinnedModel* const model) {
    collision_.Center      = model->GetPosition() + SimpleMath::Vector3(0, CENTER_PLUS_Y_VALUE_, 0);
    collision_.Orientation = model->GetRotationQuaternion();
}