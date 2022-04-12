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
	void Render2D();
	void PlayerCollision(BoundingOrientedBox player);
	void BossCollision(BoundingOrientedBox boss);

private:
	BoundingOrientedBox player_collision_;
	BoundingOrientedBox boss_collision_;

	bool hit_flg_;
	DX9::SPRITEFONT font;

};