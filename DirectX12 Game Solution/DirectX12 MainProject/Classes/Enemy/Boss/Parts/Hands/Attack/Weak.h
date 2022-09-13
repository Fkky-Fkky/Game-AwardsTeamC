#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Weak : public BossAttack {
public:
	Weak() {
		weak_state_ = ATK_CANCEL;
		time_delta_ = 0.0f;
		time_ = 0.0f;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
		rot_r_ = SimpleMath::Vector3::Zero;
		rot_l_ = SimpleMath::Vector3::Zero;
	}
	~Weak() {};
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void AtkCancel(HandManager* const hand_m);
	void Ready(const ObjectManager* const obj_m);
	void BossWeak(const ObjectManager* const obj_m);
	void InitialPosMove();

	int weak_state_;

	float time_delta_;
	float time_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 pos_l_;
	SimpleMath::Vector3 rot_r_;
	SimpleMath::Vector3 rot_l_;

	enum WEAK_STATE {
		ATK_CANCEL,
		READY,
		WEAK,
		INITIAL_POS_MOVE,
		ACTION_END
	};
};