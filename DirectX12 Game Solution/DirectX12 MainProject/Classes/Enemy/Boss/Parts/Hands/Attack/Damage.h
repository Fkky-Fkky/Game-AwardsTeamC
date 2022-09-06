#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Damage : public BossAttack {
public:
	Damage() {
		damage_state_ = DAMAGE;
		time_delta_ = 0.0f;
		wait_time_  = 0.0f;
		is_r_hand_break_	  = false;
		is_l_hand_break_	  = false;
		is_double_hand_break_ = false;
		is_r_hand_move_end_   = false;
		is_l_hand_move_end_   = false;
		pos_r_ = SimpleMath::Vector3::Zero;
		pos_l_ = SimpleMath::Vector3::Zero;
		rot_r_ = SimpleMath::Vector3::Zero;
		rot_l_ = SimpleMath::Vector3::Zero;

	}
	~Damage(){};
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);

private:
	void HandDamage(const ObjectManager* const obj_m);
	void Wait();
	void OffScreenMove();
	void Reset();
	void InitialPosMove();

	int damage_state_;

	float time_delta_;
	float wait_time_;

	bool is_r_hand_break_;
	bool is_l_hand_break_;
	bool is_double_hand_break_;
	bool is_r_hand_move_end_;
	bool is_l_hand_move_end_;

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
		ACTION_END,
		CHANGE_WEAK_STATE,
	};

	const float MAX_WAIT_TIME_ = 0.5f;
};