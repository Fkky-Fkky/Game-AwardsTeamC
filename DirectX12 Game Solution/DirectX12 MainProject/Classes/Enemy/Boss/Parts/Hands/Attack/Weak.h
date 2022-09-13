#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Weak : public BossAttack {
public:
	Weak() {
		weak_state_ = ATK_CANCEL;
		time_delta_  = 0.0f;
		weak_time_y_ = 0.0f;
		weak_y_ = 0.0f;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
		rot_r_ = SimpleMath::Vector3::Zero;
		rot_l_ = SimpleMath::Vector3::Zero;
	}
	~Weak() {};
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void AtkCancel(HandManager* const hand_m);
	void Ready(HandManager* const hand_m);
	void ReadyR();
	void ReadyL();
	void BossWeak(const ObjectManager* const obj_m, HandManager* const hand_m);
	void InitialPosMove();

	int weak_state_;

	float time_delta_;
	float weak_time_y_;
	float weak_y_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 pos_l_;
	SimpleMath::Vector3 rot_r_;
	SimpleMath::Vector3 rot_l_;

	const float WEAK_ROT_X_ = 150.0f;
	const float WEAK_POS_X_ = 18.0f;
	const float WEAK_POS_Y_ = 3.0f;

	enum WEAK_STATE {
		ATK_CANCEL,
		READY,
		WEAK,
		INITIAL_POS_MOVE,
		ACTION_END
	};
};