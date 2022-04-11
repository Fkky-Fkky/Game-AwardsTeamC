#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerTestCamera {
public:
	PlayerTestCamera() {};
	~PlayerTestCamera() {};

	void Initialize();
	void Update();
	void Render();

private:
	DX9::CAMERA camera;


};