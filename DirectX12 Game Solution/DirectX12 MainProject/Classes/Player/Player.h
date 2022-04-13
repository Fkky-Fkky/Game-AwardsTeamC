#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Collision/Collision.h"

using namespace DirectX;

class Player {
public:
	Player() {};
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void Render2D();
	void HitPlayer(bool player_hit_flag);
	void HitProcessing();
	BoundingOrientedBox GetPlayerCollision() { return player_collision_; }
	BoundingOrientedBox GetPlayerAttackCollision() { return player_attack_collision_; }
	bool AttackFlag() { return attack_flg_; }

private:
	DX9::MODEL model_;
	DX9::SPRITEFONT font;

	BoundingOrientedBox player_collision_;
	DX9::MODEL player_collision_model_;

	BoundingOrientedBox player_attack_collision_;
	DX9::MODEL player_attack_collision_model_;

	SimpleMath::Vector3 pos_player_;
	SimpleMath::Vector3 rot_player_;

	float attack_x_;
	float attack_time_;
	bool attack_flg_;

	bool jump_flg_;

	float v0_;
	float time_;
	float gravity_;

	float ground_y_;

	int player_hp_;
	bool hit_flag_;

	Collision collision;
};