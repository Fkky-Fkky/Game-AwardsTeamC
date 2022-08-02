#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;
class Player;

class PlayerAttackColision {
public:
	PlayerAttackColision() {
		attack_time_ = 0.0f;
		is_player_attack_ = false;
		is_effect_play_	  = false;
	}
	~PlayerAttackColision() {};

	void Initialize();
	void LoadAssets(DX9::SkinnedModel* model_);
	void Update(const float deltaTime, DX9::SkinnedModel* model_, Player* player);
	void Render();

	bool IsPlayerAttack() { return is_player_attack_; }
	BoundingOrientedBox GetAttackCollision() { return collision_; }
private:
	BoundingOrientedBox collision_;
	DX9::MODEL          collision_model_;
	float attack_time_;
	bool is_player_attack_;
	bool is_effect_play_;

	const float RIGHT_ = -90.0f;
	const float RIGHT_ANGLE_ = 0.0f;
	const float LEFT_ANGLE_  = 200.0f;
	const float MAX_ATTACK_TIME_ = 3.3f;
	const float ATTACK_DISTANCE_X_ = 1.5f;
	const float ATTACK_DISTANCE_Y_ = 1.5f;
	const float COLLISION_SIZE_MULTIPLY_X_ = 0.5f;
	const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f;
	const float COLLISION_SIZE_MULTIPLY_Z_ = 0.5f;
};