#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class My_Light {
public:
	My_Light() {};
	~My_Light(){};
	void LoadAssets();
private:
	const float DIRECTION_X_ = -20.0f;
	const float DIRECTION_Y_ = -170.0f;
	const float DIRECTION_Z_ = 80.0f;
	const float LIGHT_POS_X_ = 0.0f;
	const float LIGHT_POS_Y_ = 4.0f;
	const float LIGHT_POS_Z_ = -24.0f;
	const float RANGE_ = 100.0f;
};