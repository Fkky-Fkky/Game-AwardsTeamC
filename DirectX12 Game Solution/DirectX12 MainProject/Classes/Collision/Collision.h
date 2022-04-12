#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Collision {
public:
	Collision() {};
	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void PlayerCollision(BoundingOrientedBox player);
	void Collision(BoundingOrientedBox player);

private:
	BoundingOrientedBox player_collision_;

};