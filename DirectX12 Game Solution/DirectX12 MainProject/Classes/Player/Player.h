#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Player {
public:
	Player() {};
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

private:
	DX9::MODEL model_;
	DX9::MODEL stage_;

	SimpleMath::Vector3 pos_player_;
	SimpleMath::Vector3 rot_player_;
};