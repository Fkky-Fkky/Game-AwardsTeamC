#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossHand : public BossParts{
public:
	BossHand() {
		motion_track_ = 0;
		timde_delta_ = 0.0f;
		motion_time_ = 0.0f;
		motion_time_max_ = 0.0f;
		motion_flag_ = false;
		attack_flag_ = false;
		is_vertical_shake_ = false;
		is_side_shake_ = false;
	}

	~BossHand() {};
	virtual void Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote);
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render()const;

	void SetHandPos(const SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(const SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(const bool attack_flag) { attack_flag_ = attack_flag; }
	void SetHandMotion(const int hand_motion);
	void SetVerticalShakeFlag(const bool enable) { is_vertical_shake_ = enable; }
	void SetSideShakeFlag(const bool enable) { is_side_shake_ = enable; }
	bool GetAttackFlag() const { return attack_flag_; }
	bool IsVerticalShake() const { return is_vertical_shake_; }
	bool IsSideShake() const { return is_side_shake_; }
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
	bool motion_flag_;
	bool attack_flag_;
	bool is_vertical_shake_;
	bool is_side_shake_;

	const int HAND_HP_MAX_ = 3;
	const int MOTION_MAX_  = 5;
	const float BACK_MOTION_TIME_ = 0.96f;
	const float ATK_MOTION_TIME_  = 0.96f;
	const float COLLSION_SIZE_X_ = 1.7f;
	const float COLLSION_SIZE_Y_ = 0.6f;
	const float COLLSION_SIZE_Z_ = 2.0f;
	const float HAND_SCALE = 0.8f;
protected:

	BoundingOrientedBox collision;
	DX9::MODEL collision_model;

	const float INITIAL_POS_Y_ = 13.0f;
	const float INITIAL_POS_Z_ = 10.0f;
	const float INITIAL_ROT_X_ = 30.0f;
	const float INITIAL_ROT_Y_ = 90.0f;
};