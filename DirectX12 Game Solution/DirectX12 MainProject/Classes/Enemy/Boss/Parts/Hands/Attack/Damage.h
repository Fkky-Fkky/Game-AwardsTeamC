#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Damage : public BossAttack {
public:
	Damage() {
		damage_state_ = DAMAGE;
		time_delta_ = 0.0f;
		wait_time_  = 0.0f;
		is_handmove_end_r_ = false;
		is_handmove_end_l_ = false;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
		rot_r_ = SimpleMath::Vector3::Zero;
		rot_l_ = SimpleMath::Vector3::Zero;

	}
	~Damage(){};
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void HandDamage(ObjectManager* obj_m);
	void Wait();
	void OffScreenMove();
	void Reset();
	void InitialPosMove();

	int damage_state_;

	float time_delta_;
	float wait_time_;

	bool is_handmove_end_r_;
	bool is_handmove_end_l_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 pos_l_;
	SimpleMath::Vector3 rot_r_;
	SimpleMath::Vector3 rot_l_;

	enum DAMAGE_STATE_ {
		DAMAGE,
		WAIT,
		OFF_SCREEN_MOVE,
		RESET,
		INITIAL_POS_MOVE,
		ACTION_END
	};

	const float MAX_WAIT_TIME_ = 0.5f;
};