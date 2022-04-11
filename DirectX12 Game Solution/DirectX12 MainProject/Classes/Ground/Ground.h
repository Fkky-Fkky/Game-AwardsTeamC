#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Ground {
public:
	Ground() {};
	~Ground() {};

	void Initialize();
	void LoadAssets();
	void Render();

private:
	DX9::MODEL stage_;
};