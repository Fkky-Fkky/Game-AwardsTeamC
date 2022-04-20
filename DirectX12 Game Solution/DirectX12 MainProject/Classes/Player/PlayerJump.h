#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerJump {
public:
	PlayerJump();
	~PlayerJump() {};

	void Update(const float deltaTime, SimpleMath::Vector3& pos_);

private:
	float time_;
	bool flag_;

	const float GRAVITY_  = 0.045f;
	const float V0_       = 0.8f;
	const float GROUND_Y_ = 0.0f;
};