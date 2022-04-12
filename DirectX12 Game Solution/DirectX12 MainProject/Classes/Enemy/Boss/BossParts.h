#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class BossAttack;

class BossParts {
public:
	void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	void LoadAssets(LPCWSTR file_name);
	void Render();

protected:
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;
	DX9::MODEL model;
};