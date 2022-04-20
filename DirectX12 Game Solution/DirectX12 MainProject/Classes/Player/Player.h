#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Collision/Collision.h"

#include "Classes/Player/PlayerMove.h"
#include "Classes/Player/PlayerJump.h"

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
	SimpleMath::Vector3 GetPlayerPosition() { return pos_; }

private:
	DX9::MODEL model_;
	DX9::SPRITEFONT font;

	BoundingOrientedBox player_collision_;
	DX9::MODEL player_collision_model_;

	BoundingOrientedBox player_attack_collision_;
	DX9::MODEL player_attack_collision_model_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

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
	PlayerMove player_move_;
	PlayerJump player_jump_;
};