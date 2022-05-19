#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossCore : public BossParts {
public:
	BossCore();
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
	int core_hp_;
	bool hit_flag_;

	SimpleMath::Vector3 core_pos_;

	const int BOSS_MAX_HP_ = 30;
};
