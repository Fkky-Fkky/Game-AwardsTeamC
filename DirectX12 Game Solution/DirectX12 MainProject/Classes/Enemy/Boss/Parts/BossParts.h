#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class BossParts {
public:
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime){};
	virtual void Render();

protected:
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;
	DX9::MODEL model;
};