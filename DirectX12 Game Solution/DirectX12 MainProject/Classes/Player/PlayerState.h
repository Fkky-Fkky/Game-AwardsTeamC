#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerState {
public:
	virtual void Update(const float deltaTime, SimpleMath::Vector3& pos, SimpleMath::Vector3& rote) = 0;
};