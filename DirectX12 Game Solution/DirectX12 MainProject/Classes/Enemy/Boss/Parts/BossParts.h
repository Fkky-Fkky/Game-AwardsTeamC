#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class BossParts {
public:
	virtual void Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote);
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render()const;

protected:
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;
	DX9::SKINNEDMODEL model_;
};