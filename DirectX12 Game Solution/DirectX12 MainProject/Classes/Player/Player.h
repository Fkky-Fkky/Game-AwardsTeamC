#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Player {
public:
	Player() {};
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();

private:
	DX9::MODEL model_;
	DX9::MODEL stage_;

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
};