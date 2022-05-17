#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerAttackColision {
public:
	PlayerAttackColision() {
		attack_flg_ = false;
		attack_time_ = 0.0f;
	}
	~PlayerAttackColision() {};

	void LoadAssets(DX9::Model* model_);
	void Update(const float deltaTime, DX9::Model* model_);
	void Render();

	bool GeatAttackFlag() { return attack_flg_; }
	BoundingOrientedBox GetAttackCollision() { return collision_; }
private:
	BoundingOrientedBox collision_;
	DX9::MODEL          collision_model_;
	float attack_time_;
	bool attack_flg_;

	const float MAX_ATTACK_TIME_ = 0.3f;
	const float ATTACK_DISTANCE_X_ = 1.5f;
	const float ATTACK_DISTANCE_Y_ = 1.5f;
};