#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerRightMove.h"
#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerAttack.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"
#include "Classes/Player/PlayerWait.h"
#include "Classes/Player/PlayerState.h"
#include "Classes/Player/PlayerDamage.h"

using namespace DirectX;

class ObjectManager;

enum class PLAYER_STATE {
	WAIT,
	RIGHT_MOVE,
	LEFT_MOVE,
	JUMP,
	ATTACK,
	DAMAGE
};

enum class PLAYER_MOTION {
	WAIT,
	ATTACK,
	MOVE,
	JUMP,
	DAMAGE
};

class Player {
public:
	Player() {
		player_action_state_ = PLAYER_STATE::WAIT;
		player_motion_track_ = 0;
		player_state_ = nullptr;
		jump_motion_time_ = 0.0f;
		initialize_stop_flag_ = false;
		is_jump_motion_play_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
	}
	~Player() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m);
	void Render()const;
	void Render2D()const;

	void SwitchState(const PLAYER_STATE state);
	void SetPlayerPosition(const SimpleMath::Vector3 position) { pos_ = position; }
	void SetPlayerRotation(const SimpleMath::Vector3 rotation) { rot_ = rotation; }
	void SetMotion(const PLAYER_MOTION player_motion);
	void SetStopInitializeFlag(const bool enable) { initialize_stop_flag_ = enable; }
	void PlayAvoidSE()const;
	void PlayJumpSE()const;
	float GetPlayerHP() const { return player_dmg_.GetPlayerHP(); }
	bool IsPlayerAttackStart() const { return player_attack_.IsPlayerAttackStart(); }
	bool IsPlayerAttack() const { return player_attack_colision_.IsPlayerAttack(); }
	SimpleMath::Vector3 GetPlayerPosition() const { return pos_; }
	SimpleMath::Vector3 GetPlayerRotation()const { return rot_; }
	BoundingOrientedBox GetPlayerCollision() const{ return player_colision_.GetColision(); }
	BoundingOrientedBox GetPlayerAttackCollision() const{ return player_attack_colision_.GetAttackCollision(); }

private:
	void ResetPlayerMotion()const;
	void JumpMotion(const float deltaTime);
	PLAYER_MOTION ConvertToMotion(const PLAYER_STATE player_state)const;

	DX9::SKINNEDMODEL model_;
	DX9::SPRITEFONT font;

	XAudio::SOUNDEFFECT avoid_se_;
	XAudio::SOUNDEFFECT jump_se_;

	PLAYER_STATE player_action_state_;
	int player_motion_track_;
	float jump_motion_time_;

	bool initialize_stop_flag_;
	bool is_jump_motion_play_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	const int MOTION_MAX_ = 5;
	const float RIGHT_WARD_ = -90.0f;

	player::PlayerRightMove      player_right_move_;
	player::PlayerLeftMove		 player_left_move_;
	player::PlayerJump           player_jump_;
	player::PlayerAttack		 player_attack_;
	player::PlayerColision       player_colision_;
	player::PlayerAttackColision player_attack_colision_;
	player::PlayerWait			 player_wait_;
	player::PlayerDamage		 player_dmg_;
	player::PlayerState*		 player_state_;
};