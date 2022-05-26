#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerRightMove.h"
#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"
#include "Classes/Player/PlayerAvoid.h"
#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/PlayerState.h"
#include "Classes/Player/PlayerDamage.h"

using namespace DirectX;

enum class PLAYER_STATE {
	WAIT,
	RIGHT_MOVE,
	LEFT_MOVE,
	JUMP,
	AVOID,
	DAMAGE
};

enum class PLAYER_MOTION {
	MOVE,
	ATTACK,
	KNOCK_BACK,
	WAIT
};

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
	void SwitchState(PLAYER_STATE state);
	void SetPlayerPosition(SimpleMath::Vector3 position) { pos_ = position; }
	void SetPlayerRotation(SimpleMath::Vector3 rotation) { rot_ = rotation; }
	void SetMotion(PLAYER_MOTION motion_track);
	float GetPlayerHP() { return player_hp_; }
	bool AttackFlag() { return player_attack_colision_.GeatAttackFlag(); }
	bool IsPlayerInvincible() { return player_avoid_.IsInvincible(); }
	SimpleMath::Vector3 GetPlayerPosition() { return pos_; }
	SimpleMath::Vector3 GetPlayerRotation() { return rot_; }
	BoundingOrientedBox GetPlayerCollision() { return player_colision_.GetColision(); }
	BoundingOrientedBox GetPlayerAttackCollision() { return player_attack_colision_.GetAttackCollision(); }
	PlayerColision* GetColision() { return &player_colision_; }

private:
	void HitProcessing();

	DX9::SKINNEDMODEL model_;
	DX9::SPRITEFONT font;

	float player_hp_;

	bool hit_flag_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	const int MOTION_MAX_ = 4;

	PlayerRightMove      player_right_move_;
	PlayerLeftMove		 player_left_move_;
	PlayerJump           player_jump_;
	PlayerColision       player_colision_;
	PlayerAttackColision player_attack_colision_;
	PlayerAvoid			 player_avoid_;
	PlayerWait			 player_wait_;
	PlayerDamage		 player_dmg_;
	PlayerState*		 player_state_;
};