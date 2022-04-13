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
	void Render2D();
	void HitPlayerAttack(bool core_hit_flag_);
	void HitProcessing();
	BoundingOrientedBox GetSmallEnemyCollision() { return collision_; }
	BoundingOrientedBox GetCoreCollision() { return collision_2; }

private:

	DX9::MODEL model_;
	DX9::SPRITEFONT font;

	BoundingOrientedBox collision_;
	DX9::MODEL collision_model_;

	BoundingOrientedBox collision_2;
	DX9::MODEL collision_model_2;

	SimpleMath::Vector3 position_;
	bool hit_flag_;
	int core_hp_;

	Collision collision;
};