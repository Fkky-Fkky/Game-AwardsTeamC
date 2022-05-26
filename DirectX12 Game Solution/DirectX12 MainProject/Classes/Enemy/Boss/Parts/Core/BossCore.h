#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"
#include "Base/DX12Effekseer.h"

class BossCore : public BossParts {
public:
	BossCore() {
		core_hp_  = 0;
		hit_flag_ = false;
		core_pos_ = SimpleMath::Vector3::Zero;
		hit_efc_  = nullptr;
	}

	virtual void Initialize();
	virtual void LoadAssets();
	virtual void Update(const float deltaTime, bool core_hit_flag);
	void Render2D();

	int GetBossHP() { return core_hp_; }
	BoundingOrientedBox GetCoreCollision() { return collision_; }
private:
	void HitPlayerAttack(bool core_hit_flag);
	void HitProcessing();

	BoundingOrientedBox collision_;
	DX9::SPRITEFONT font;
	EFFECT hit_efc_;

	int core_hp_;
	bool hit_flag_;
	SimpleMath::Vector3 core_pos_;

	const int BOSS_MAX_HP_ = 30;
	const float BOSS_CORE_POS_Y_ = 9.0f;
};
