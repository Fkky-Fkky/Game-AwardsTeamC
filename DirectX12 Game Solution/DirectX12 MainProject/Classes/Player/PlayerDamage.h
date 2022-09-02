#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerDamage : public PlayerState {
public:
	PlayerDamage() {
		player_hp_ = PLAYER_HP_MAX_;
		dmg_time   = 0.0f;
		hit_flag_  = false;
	}
	~PlayerDamage() {};

	virtual void Initialize();
	virtual void Update(const float deltaTime, Player& player);

	float GetPlayerHP() { return player_hp_; }

private:
	void HitProcessing();

	float player_hp_;
	float dmg_time;
	bool hit_flag_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	const float PLAYER_HP_MAX_ = 30.0f;
	const float FALL_SPEED_	   = 15.0f;
	const float DMG_TIME_MAX_  = 0.6f;
};