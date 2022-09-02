#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include "Base/DX12Effekseer.h"

class Boss;
class ObjectManager;

using namespace DirectX;

class BossAttack {
public:
	virtual void Initialize(BossHand* boss_handL, BossHand* bosshandR) {
		boss_handL_ = boss_handL;
		boss_handR_ = bosshandR;
	};
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) = 0;

protected:
	BossHand* boss_handL_;
	BossHand* boss_handR_;

	const float HAND_R_INITIAL_POS_X_ = -13.0f;
	const float HAND_L_INITIAL_POS_X_ = 13.0f;
	const float HAND_INITIAL_POS_Y_ = 13.0f;
	const float HAND_INITIAL_POS_Z_ = 10.0f;

	const float HAND_INITIAL_ROT_X_ = 30.0f;
	const float HAND_R_INITIAL_ROT_Y_ = -90.0f;
	const float HAND_L_INITIAL_ROT_Y_ = 90.0f;

	const float HAND_LIMIT_POS_X_ = 70.0f;
	const float HAND_ROCK_LIMIT_POS_Y_ = 3.0f;
	const float HAND_RETURN_POS_X_ = 30.0f;

	const float SLAP_POS_Y_ = 0.5f;
	const float SLAP_POS_Z_ = -2.0f;
	const float SLAP_ROT_X_ = 30.0f;
	const float SLAP_SPEED_X_ = 0.5f;
	const float SLAP_SPEED_Y_ = 2.0f;
	const float SLAP_GRAVITY_X_ = 1.3f;
	const float SLAP_GRAVITY_Y_ = 5.0f;

	const float WAIT_TIME_MAX_ = 0.7f;

	const float BEAT_SPEED_ = 3.5f;
	const float BEAT_GRAVITY_ = 15.0f;
	const float BEAT_HAND_ROCK_ROT_X_ = 90.0f;

	const float MOVE_SPEED_X_ = 20.0f;
	const float MOVE_SPEED_Y_ = 10.0f;
	const float MOVE_SPEED_Z_ = 10.0f;
	const float ROTE_SPEED_ = 100.0f;

	const float HALF_ = 0.5f;

	enum ACTION_STATE {
		HAND_CHECK,
		READY,
		WAIT,
		ATTACK,
		RESET,
		RETURN,
		ACTION_END
	};

	enum HAND_MOTION {
		WAIT_MOTION,
		PAPER,
		PAPER_BACK,
		ROCK,
		ROCK_BACK
	};
};