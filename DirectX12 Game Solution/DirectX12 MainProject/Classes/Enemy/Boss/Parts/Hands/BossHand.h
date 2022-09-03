#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossHand : public BossParts{
public:
	BossHand() {
		hand_hp_ = 0;
		motion_track_ = 0;
		timde_delta_ = 0.0f;
		motion_time_ = 0.0f;
		motion_time_max_ = 0.0f;
		bezier_t = 0.0f;
		motion_flag_ = false;
		attack_flag_ = false;
		is_vertical_shake_ = false;
		is_side_shake_ = false;
	}

	~BossHand() {};
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render();
	void Render2D(float pos_x);

	void HandDamageProcess();
	void HandHPHeal();
	void SetHandPos(const SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(const SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(const bool attack_flag) { attack_flag_ = attack_flag; }
	void SetHandMotion(const int hand_motion);
	void SetVerticalShakeFlag(const bool enable) { is_vertical_shake_ = enable; }
	void SetSideShakeFlag(const bool enable) { is_side_shake_ = enable; }
	int  GetHandHp() const { return hand_hp_; }
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
	void HandMotionWait();

	enum HAND_MOTION {
		WAIT,
		PAPER,
		PAPER_BACK,
		ROCK,
		ROCK_BACK
	};

	int hand_hp_;
	int motion_track_;
	float motion_time_;
	float motion_time_max_;
	float timde_delta_;
	float bezier_t;
	bool motion_flag_;
	bool attack_flag_;
	bool is_vertical_shake_;
	bool is_side_shake_;

	const int HAND_HP_MAX_ = 3;
	const int MOTION_MAX_  = 5;
	const float BACK_MOTION_TIME_ = 0.96f;
	const float ATK_MOTION_TIME_  = 0.96f;
protected:

	BoundingOrientedBox collision;
	DX9::MODEL collision_model;
	DX9::SPRITEFONT font_;

	const float INITIAL_POS_Y_ = 13.0f;
	const float INITIAL_POS_Z_ = 10.0f;
	const float INITIAL_ROT_X_ = 30.0f;
	const float INITIAL_ROT_Y_ = 90.0f;
};