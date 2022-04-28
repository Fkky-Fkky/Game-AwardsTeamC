#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerAttackColision {
public:
	PlayerAttackColision() {};
	~PlayerAttackColision() {};

	void LoadAssets(DX9::Model* model_);
	void Update(const float deltaTime, DX9::Model* model_);
	void Render();


private:
	BoundingOrientedBox collision_;
	DX9::MODEL          collision_model_;
};