#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class My_Camera {
public:
	My_Camera() {};
	~My_Camera() {};

	void Initialize();
	void Update();
	void Render();

private:
	DX9::CAMERA camera;


};