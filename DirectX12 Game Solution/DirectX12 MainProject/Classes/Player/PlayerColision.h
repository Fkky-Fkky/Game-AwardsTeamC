#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerColision {
public:
	PlayerColision() {};
	~PlayerColision() {};

	void LoadAssets(DX9::SkinnedModel* model_);
	void Update(const float deltaTime, DX9::SkinnedModel* model_);
	void Render();
	BoundingOrientedBox GetColision() const { return collision_; }

private:
	BoundingOrientedBox collision_;
	DX9::MODEL          collision_model_;

	const float COLLISION_SIZE_MULTIPLY_X_ = 0.5f;
	const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f;
	const float COLLISION_SIZE_MULTIPLY_Z_ = 0.5f;
	const float CENTER_PLUS_Y_VALUE_       = 2.0f;
};