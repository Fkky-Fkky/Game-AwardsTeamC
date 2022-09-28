#include "Classes/Player/PlayerCollision.h"

void player::PlayerCollision::LoadAssets(DX9::SkinnedModel* const model) {
    collision_ = model->GetBoundingOrientedBox();

    collision_.Extents = SimpleMath::Vector3(   //“–‚½‚è”»’è‚ÌƒTƒCƒY’²®
        collision_.Extents.x * COLLISION_SIZE_MULTIPLY_X_,
        collision_.Extents.y * COLLISION_SIZE_MULTIPLY_Y_,
        collision_.Extents.z * COLLISION_SIZE_MULTIPLY_Z_
    );
}

void player::PlayerCollision::Update(const float deltaTime, const DX9::SkinnedModel* const model) {
    collision_.Center      = model->GetPosition() + SimpleMath::Vector3(0, CENTER_PLUS_Y_VALUE_, 0);
    collision_.Orientation = model->GetRotationQuaternion();
}