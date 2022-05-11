#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include "Base/DX12Effekseer.h"

class Boss;

using namespace DirectX;

class BossAttack {
public:
	virtual void Initialize(BossHand* boss_handL, BossHand* bosshandR) {
		boss_handL_ = boss_handL;
		boss_handR_ = bosshandR;
	};
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss) = 0;

protected:
	BossHand* boss_handL_;
	BossHand* boss_handR_;

	const float HAND_R_INITIAL_POS_X_ = -13.0f;
	const float HAND_L_INITIAL_POS_X_ = 13.0f;
	const float HAND_INITIAL_POS_Y_ = 10.0f;
	const float HAND_INITIAL_POS_Z_ = 3.0f;

	const float SLAP_SPEED_ = 1.5f;
	const float SLAP_GRAVITY_ = 5.0f;

	const float BEAT_SPEED_ = 1.5f;
	const float BEAT_GRAVITY_ = 15.0f;
	const float MOVE_SPEED_X_ = 30.0f;
	const float MOVE_SPEED_Y_ = 10.0f;
	const float ROTE_SPEED_ = 1.0f;

	const float HALF_ = 0.5f;

};