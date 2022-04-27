#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"
#include <random>

using namespace DirectX;

class BossHand : public BossParts{
public:
	BossHand();
	~BossHand() {};
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render();
	//virtual void Attack();
	virtual void SetBossState(int state) { boss_state = state; }
	bool GetAttackFlag() { return attack_flag; }
	BoundingOrientedBox GetHandCollision() { return collision; }
	SimpleMath::Vector3 GetHandPos() { return position; }
	SimpleMath::Vector3 GetRotation() { return rotation; }
	void SetHandPos(SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(bool attack_flag_) { attack_flag = attack_flag_; }


private:

	void SusiZanmai();
	void RandomAction();

	float bezier_t;
	float time_delta;

	std::mt19937 randomEngine;
	std::uniform_int_distribution<int> randomDist;
	float wait_time;

	int boss_state;
	enum BOSS_STATE {
		WAIT,
		RIGHT_SLAP,
		LEFT_SLAP,
		RIGHT_BEAT,
		LEFT_BEAT
	};

protected:
	bool attack_flag;

	BoundingOrientedBox collision;
	DX9::MODEL collision_model;
};