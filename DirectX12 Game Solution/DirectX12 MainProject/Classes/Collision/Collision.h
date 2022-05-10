#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Collision/ObjectManager.h"

using namespace DirectX;

class Collision {
public:
	Collision() {};
	~Collision() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, bool attack_flag_, bool boss_r_attack_flag_, bool boss_l_attack_flag_, ObjectManager& obj_m_);
	void Render();
	void Render2D();
	void PlayerCollision(BoundingOrientedBox player);
	void PlayerAttackCollision(BoundingOrientedBox player_attack_);
	void BossHandRightCollision(BoundingOrientedBox boss_hand_right_);
	void BossHandLeftCollision (BoundingOrientedBox boss_hand_left_);
	void CoreCollision(BoundingOrientedBox core);
	bool GetHitFlag() { return hit_flg_; }
	bool GetHitAttackFlag() { return hit_attack_flg_; }

private:
	BoundingOrientedBox player_collision_;
	BoundingOrientedBox player_attack_collision_;
	BoundingOrientedBox boss_hand_right_collision_;
	BoundingOrientedBox boss_hand_left_collision_;
	BoundingOrientedBox core_collision_;

	bool hit_flg_;
	bool hit_attack_flg_;
	DX9::SPRITEFONT font;

	ObjectManager object_manager_;
};