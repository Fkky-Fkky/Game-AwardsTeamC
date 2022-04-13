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
	void Update(const float deltaTime, bool attack_flag_);
	void Render();
	void Render2D();
	void PlayerCollision(BoundingOrientedBox player);
	void PlayerAttackCollision(BoundingOrientedBox player_attack_);
	void BossCollision(BoundingOrientedBox boss);
	void CoreCollision(BoundingOrientedBox core);
	bool GetHitFlag() { return hit_flg_; }
	bool GetHitAttackFlag() { return hit_attack_flg_; }

private:
	BoundingOrientedBox player_collision_;
	BoundingOrientedBox player_attack_collision_;
	BoundingOrientedBox boss_collision_;
	BoundingOrientedBox core_collision_;

	bool hit_flg_;
	bool hit_attack_flg_;
	DX9::SPRITEFONT font;

};