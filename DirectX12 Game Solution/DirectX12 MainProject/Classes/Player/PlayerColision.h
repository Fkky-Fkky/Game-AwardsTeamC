#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerColision {
public:
	PlayerColision() {};
	~PlayerColision() {};

	void LoadAssets(DX9::Model* model_);
	void Update(const float deltaTime, DX9::Model* model_);
	void Render();

private:
	BoundingOrientedBox collision_;
	DX9::MODEL          collision_model_;

	const float EXTECTS_X_MULUTIPLY_VALUE_ = 0.65f;
	const float EXTECTS_Y_MULUTIPLY_VALUE_ = 1.35f;
	const float CENTER_PLUS_Y_VALUE_       = 1.5f;
};