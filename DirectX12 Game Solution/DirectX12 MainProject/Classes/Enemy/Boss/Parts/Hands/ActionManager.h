#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include <random>
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class ObjectManager;
class HandManager;

class ActionManager {
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* const obj_m_, HandManager* const hand_m);
};