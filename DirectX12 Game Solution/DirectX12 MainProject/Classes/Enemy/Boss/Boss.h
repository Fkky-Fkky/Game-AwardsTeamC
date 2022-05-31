#pragma once
#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Body/BossBody.h"
#include "Classes/Enemy/Boss/Parts/Core/BossCore.h"
#include "Classes/Enemy/Boss/Parts/Hands/LeftHand/BossHandL.h"
#include "Classes/Enemy/Boss/Parts/Hands/RightHand/BossHandR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"
#include <random>
#include "Base/DX12Effekseer.h"

using namespace DirectX;

class ObjectManager;

class Boss {
public:
	Boss() {
		attack = nullptr;
		attack_state = WAIT;
		action_end_flag = false;
		beat_effect_ = nullptr;
	}

	~Boss() {};

	void Initialize();
	void LoadAseets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();
	void Render2D();

	void ActionEnd();
	void RandomAttackState();
	void PlaySlapSE();
	void PlayBeatSE();
	void PlayBeatEffect(SimpleMath::Vector3 effect_pos);
	int GetBossHP() { return core.GetBossHP(); }
	bool GetLHandAttackFlag() { return hand_l.GetAttackFlag(); }
	bool GetRHandAttackFlag() { return hand_r.GetAttackFlag(); }
	BoundingOrientedBox GetLHandCollision() { return hand_l.GetHandCollision(); }
	BoundingOrientedBox GetRHandCollision() { return hand_r.GetHandCollision(); }
	BoundingOrientedBox GetCoreCollision() { return core.GetCoreCollision(); }

private:
	void SwitchStateAttack();
	void SwitchStateWait();
	BossBody body;
	BossCore core;
	BossHandL hand_l;
	BossHandR hand_r;

	BossAttack* attack;
	std::mt19937 randomEngine;
	std::uniform_int_distribution<int> randomDist;
	int attack_state;

	bool action_end_flag;
	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT,
		BEAT_RUSH_R,
		DOUBLE_SLAP
	};

	EFFECT beat_effect_;

	XAudio::SOUNDEFFECT slap_se_;
	XAudio::SOUNDEFFECT	beat_se_;
};