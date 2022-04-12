#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Collision/Collision.h"

using namespace DirectX;

class SmallEnemy {
public:
	SmallEnemy() {};
	~SmallEnemy() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	BoundingOrientedBox GetSmallEnemyCollision() { return collision_; }

private:

	DX9::MODEL model_;

	BoundingOrientedBox collision_;
	DX9::MODEL collision_model_;

	SimpleMath::Vector3 position_;

	Collision collision;
};