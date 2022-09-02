#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"
#include "Base/DX12Effekseer.h"

class Boss;

class BossCore : public BossParts {
public:
	BossCore() {
		core_hp_  = 0;
		time_delta_ = 0.0f;
		core_weak_time_ = 0.0f;
		hit_flag_ = false;
		core_pos_ = SimpleMath::Vector3::Zero;
		hit_efc_  = nullptr;
	}

	virtual void Initialize();
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, bool core_hit_flag, Boss* boss);
	virtual void Render();
	void Render2D();

	float GetBossHP() { return core_hp_; }
	BoundingOrientedBox GetCoreCollision() { return collision_; }
private:
	void CoreMove(bool weak_state);
	void HitPlayerAttack(bool core_hit_flag);
	void HitProcessing();

	BoundingOrientedBox collision_;
	DX9::MODEL collision_model_;
	DX9::MODEL core_;
	DX9::SPRITEFONT font;
	EFFECT hit_efc_;

	float core_hp_;
	float time_delta_;
	float core_weak_time_;
	bool hit_flag_;
	SimpleMath::Vector3 core_pos_;

	const float BOSS_MAX_HP_ = 30.0f;
	const float CORE_INTIAL_POS_Y_ = -2.0f;
	const float CORE_INTIAL_POS_Z_ = 1.0f;
	const float CORE_MOVE_SPEED_Y_ = 10.0f;
	const float CORE_MOVE_DEST_Y_ = 1.5f;
};
