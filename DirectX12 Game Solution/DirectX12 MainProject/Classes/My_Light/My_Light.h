#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class My_Light {
public:

	void LoadAssets();

private:
	const float LIGHT_POS_X_ = 10.0f;
	const float LIGHT_POS_Y_ = 15.0f;
	const float LIGHT_POS_Z_ = 3.0f;
};