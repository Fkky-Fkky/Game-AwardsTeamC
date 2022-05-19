#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerTestCamera {
public:
	PlayerTestCamera() {};
	~PlayerTestCamera() {};

	void Initialize();
private:
	DX9::CAMERA camera;

	const float CAMERA_POS_Y_ = 2.0f;
	const float CAMERA_POS_Z_ = -26.0f;
	const float LOOK_AT_POS_Y = 9.0f;
};