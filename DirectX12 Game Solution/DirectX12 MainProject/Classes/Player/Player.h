#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Collision/Collision.h"

#include "Classes/Player/PlayerMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"

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
	BoundingOrientedBox GetPlayerCollision() { return ; }
	BoundingOrientedBox GetPlayerAttackCollision() { return ; }
	bool AttackFlag() { return attack_flg_; }
	SimpleMath::Vector3 GetPlayerPosition() { return pos_; }
	PlayerColision* GetColision() { return &player_colision_; }

private:
	DX9::MODEL model_;
	DX9::SPRITEFONT font;

	/*BoundingOrientedBox player_collision_;
	DX9::MODEL player_collision_model_;

	BoundingOrientedBox player_attack_collision_;
	DX9::MODEL player_attack_collision_model_;*/

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	float attack_x_;
	float attack_time_;
	bool attack_flg_;

	int player_hp_;
	bool hit_flag_;

	Collision collision;
	PlayerMove           player_move_;
	PlayerJump           player_jump_;
	PlayerColision       player_colision_;
	PlayerAttackColision player_attack_colision_;
};