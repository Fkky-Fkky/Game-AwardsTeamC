#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerDamage : public PlayerState {
public:
	PlayerDamage() {
		player_hp_ = PLAYER_HP_MAX_;
		dmg_time   = 0.0f;
		knock_back_dest_ = 0.0f;
		hit_flag_  = false;
		one_process_flag_ = false;
	}
	~PlayerDamage() {};

	virtual void Initialize();
	virtual void Update(const float deltaTime, Player* const player);

	float GetPlayerHP() const { return player_hp_; }

private:
	void HitProcessing();

	float player_hp_;
	float dmg_time;
	float knock_back_dest_;
	bool hit_flag_;
	bool one_process_flag_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;
	const float ADD_DEST_ = 3.0f;
	const float KNOCK_BACK_SPEED_ = 20.0f;
	const float PLAYER_HP_MAX_ = 30.0f;
	const float FALL_SPEED_	   = 15.0f;
	const float DMG_TIME_MAX_  = 0.6f;
};