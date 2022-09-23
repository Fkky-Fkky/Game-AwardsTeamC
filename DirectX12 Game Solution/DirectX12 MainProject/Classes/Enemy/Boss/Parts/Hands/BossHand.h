#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossHand : public BossParts{
public:
	BossHand() {
		motion_track_ = 0;
		timde_delta_  = 0.0f;
		motion_time_  = 0.0f;
		motion_time_max_  = 0.0f;
		motion_stop_time_ = 0.0f;
		motion_flag_	 = false;
		attack_flag_	 = false;
		is_death_motion_ = false;
	}

	~BossHand() {};
	virtual void Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote);
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);

	void PlayDeathMotion();
	void SetHandPos(const SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(const SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(const bool attack_flag) { attack_flag_ = attack_flag; }
	void SetHandMotion(const int hand_motion);
	bool IsAttack() const { return attack_flag_; }
	BoundingOrientedBox GetHandCollision() const { return collision; }
	SimpleMath::Vector3 GetHandPos() const { return position; }
	SimpleMath::Vector3 GetRotation() const { return rotation; }

private:
	void MotionStart();
	void MotionReset();
	void PlayMotion();
	void HandMotionAttack();
	void HandMotionWait()const;

	enum HAND_MOTION {
		WAIT,
		PAPER,
		PAPER_BACK,
		ROCK,
		ROCK_BACK
	};

	int motion_track_;
	float motion_time_;
	float motion_time_max_;
	float timde_delta_;
	float motion_stop_time_;
	bool motion_flag_;
	bool attack_flag_;
	bool is_death_motion_;

	const int MOTION_MAX_  = 5;
	const float BACK_MOTION_TIME_ = 0.96f;
	const float ATK_MOTION_TIME_  = 0.96f;
	const float COLLSION_SIZE_X_ = 1.7f;
	const float COLLSION_SIZE_Y_ = 0.6f;
	const float COLLSION_SIZE_Z_ = 2.0f;
	const float HAND_SCALE = 0.8f;
	const float STOP_TIME_ = 0.5f;
protected:

	BoundingOrientedBox collision;

	const float INITIAL_POS_Y_ = 50.0f;
	const float INITIAL_POS_Z_ = 10.0f;
	const float INITIAL_ROT_X_ = 30.0f;
	const float INITIAL_ROT_Y_ = 90.0f;
};