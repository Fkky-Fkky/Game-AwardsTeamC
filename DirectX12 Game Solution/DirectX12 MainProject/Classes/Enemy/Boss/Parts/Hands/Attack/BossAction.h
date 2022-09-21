#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include "Base/DX12Effekseer.h"

class HandManager;
class ObjectManager;

using namespace DirectX;

namespace boss {
	class BossAction {
	public:
		BossAction() {
			slap_speed_  = 0.0f;
			slap_y_time_ = 0.0f;
			is_se_play_	  = false;
			is_shake_set_ = false;
			boss_handL_ = nullptr;
			boss_handR_ = nullptr;
		}

		virtual void Initialize(BossHand* const boss_handL, BossHand* const bosshandR);
		virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m) = 0;

	private:
		float slap_y_time_;
		bool is_se_play_;
		bool is_shake_set_;
		const float SLAP_SPEED_Y_	= 2.0f;
		const float SLAP_GRAVITY_Y_ = 5.0f;

	protected:
		virtual void SlapAttackBase(const float deltaTime, HandManager* const hand_m);	
		virtual float SlapY(const float deltaTime);

		BossHand* boss_handL_;
		BossHand* boss_handR_;
		float slap_speed_;


		const float HAND_R_INITIAL_POS_X_ = -13.0f;
		const float HAND_L_INITIAL_POS_X_ = 13.0f;
		const float HAND_INITIAL_POS_Y_ = 13.0f;
		const float HAND_INITIAL_POS_Z_ = 10.0f;

		const float HAND_INITIAL_ROT_X_ = 30.0f;

		const float ATTACK_POS_Z_ = -2.0f;
		const float HAND_LIMIT_POS_X_ = 70.0f;
		const float HAND_ROCK_LIMIT_POS_Y_ = 3.0f;
		const float HAND_RETURN_POS_X_ = 30.0f;

		const float SLAP_POS_Y_ = 0.5f;
		const float SLAP_SPEED_MAX_X_ = 40.0f;
		const float ADD_SLAP_SPEED_ = 20.0f;

		const float WAIT_TIME_MAX_ = 0.7f;

		const float BEAT_SPEED_ = 3.5f;
		const float BEAT_GRAVITY_ = 15.0f;
		const float BEAT_HAND_ROCK_ROT_X_ = 90.0f;

		const float MOVE_SPEED_X_ = 20.0f;
		const float MOVE_SPEED_Y_ = 10.0f;
		const float MOVE_SPEED_Z_ = 20.0f;
		const float ROTE_SPEED_ = 200.0f;

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
}