#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Weak : public BossAttack {
public:
	Weak() {
		weak_state_ = READY;
		time_delta_ = 0.0f;
		weak_time_	= 0.0f;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
	}
	~Weak() {};
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void BossWeak(Boss* boss);
	void HandHeal();
	void InitilaPosMove();

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

	const float WEAK_TIME_MAX_ = 3.0f;
};