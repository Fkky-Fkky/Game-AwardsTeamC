#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

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
	float GetPlayerHP() { return player_hp_; }
	BoundingOrientedBox GetPlayerCollision() { return player_colision_.GetColision(); }
	BoundingOrientedBox GetPlayerAttackCollision() { return player_attack_colision_.GetAttackCollision(); }
	bool AttackFlag() { return player_attack_colision_.GeatAttackFlag(); }
	SimpleMath::Vector3 GetPlayerPosition() { return pos_; }
	PlayerColision* GetColision() { return &player_colision_; }

private:
	void HitProcessing();

	DX9::MODEL model_;
	DX9::SPRITEFONT font;

	/*BoundingOrientedBox player_collision_;
	DX9::MODEL player_collision_model_;

	BoundingOrientedBox player_attack_collision_;
	DX9::MODEL player_attack_collision_model_;*/

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	float player_hp_;
	bool hit_flag_;

	PlayerMove           player_move_;
	PlayerJump           player_jump_;
	PlayerColision       player_colision_;
	PlayerAttackColision player_attack_colision_;
};