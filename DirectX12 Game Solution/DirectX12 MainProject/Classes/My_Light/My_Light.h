#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class My_Light {
public:
	My_Light() {
		light_pos_ = SimpleMath::Vector3::Zero;
	}
	~My_Light(){};
	void LoadAssets();
	void Update(const float deltaTime);
private:
	D3DLIGHT9 light;

	SimpleMath::Vector3 light_pos_{};
	const float LIGHT_POS_X_ = 0.0f;
	const float LIGHT_POS_Y_ = 4.0f;
	const float LIGHT_POS_Z_ = -24.0f;
};