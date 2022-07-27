#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

#include "Classes/Player/PlayerRightMove.h"
#include "Classes/Player/PlayerLeftMove.h"
#include "Classes/Player/PlayerJump.h"
#include "Classes/Player/PlayerAttack.h"
#include "Classes/Player/PlayerColision.h"
#include "Classes/Player/PlayerAttackColision.h"
#include "Classes/Player/PlayerAvoid.h"
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
	AVOID,
	DAMAGE
};

enum class PLAYER_MOTION {
	WAIT,
	ATTACK,
	MOVE,
	JUMP
};

class Player {
public:
	Player() {
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
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();
	void Render2D();

	void SwitchState(PLAYER_STATE state);
	void SetPlayerPosition(SimpleMath::Vector3 position) { pos_ = position; }
	void SetPlayerRotation(SimpleMath::Vector3 rotation) { rot_ = rotation; }
	void SetMotion(PLAYER_MOTION player_motion);
	void SetStopInitializeFlag(bool enable) { initialize_stop_flag_ = enable; }
	void PlayAvoidSE();
	void PlayJumpSE();
	float GetPlayerHP() { return player_dmg_.GetPlayerHP(); }
	bool IsPlayerAttackStart() { return player_attack_.IsPlayerAttackStart(); }
	bool IsPlayerAttack() { return player_attack_colision_.IsPlayerAttack(); }
	bool IsPlayerInvincible() { return player_avoid_.IsInvincible(); }
	SimpleMath::Vector3 GetPlayerPosition() { return pos_; }
	SimpleMath::Vector3 GetPlayerRotation() { return rot_; }
	BoundingOrientedBox GetPlayerCollision() { return player_colision_.GetColision(); }
	BoundingOrientedBox GetPlayerAttackCollision() { return player_attack_colision_.GetAttackCollision(); }
	PlayerColision* GetColision() { return &player_colision_; }
	PLAYER_STATE GetPlayerState() { return player_action_state_; }

private:
	void ResetPlayerMotion();
	PLAYER_MOTION ConvertToMotion(PLAYER_STATE player_state);

	DX9::SKINNEDMODEL model_;
	DX9::SPRITEFONT font;

	XAudio::SOUNDEFFECT avoid_se_;
	XAudio::SOUNDEFFECT jump_se_;

	PLAYER_STATE player_action_state_;

	float jump_motion_time_;

	bool initialize_stop_flag_;
	bool is_jump_motion_play_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	const int MOTION_MAX_ = 4;
	const float RIGHT_WARD_ = -90.0f;

	PlayerRightMove      player_right_move_;
	PlayerLeftMove		 player_left_move_;
	PlayerJump           player_jump_;
	PlayerAttack		 player_attack_;
	PlayerColision       player_colision_;
	PlayerAttackColision player_attack_colision_;
	PlayerAvoid			 player_avoid_;
	PlayerWait			 player_wait_;
	PlayerDamage		 player_dmg_;
	PlayerState*		 player_state_;
};