#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Weak : public BossAttack {
public:
	Weak() {
		weak_state_ = WEAK;
		time_delta_ = 0.0f;
		weak_time_	= 0.0f;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
	}
	~Weak() {};
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);

private:
	void BossWeak(Boss* const boss);
	void HandHeal();
	void InitialPosMove();

	int weak_state_;

	float time_delta_;
	float weak_time_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 pos_l_;

	enum WEAK_STATE {
		WEAK,
		HAND_HEAL,
		INITIAL_POS_MOVE,
		ACTION_END
	};

	const float WEAK_TIME_MAX_ = 6.0f;
};