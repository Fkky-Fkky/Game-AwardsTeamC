#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class BossParts {
public:
	void Initialize(float pos_x, float pos_y, float pos_z);
	void LoadAssets(LPCWSTR file_name);
	void Update();
	void Render();

protected:
	SimpleMath::Vector3 position;
	DX9::MODEL model;
};