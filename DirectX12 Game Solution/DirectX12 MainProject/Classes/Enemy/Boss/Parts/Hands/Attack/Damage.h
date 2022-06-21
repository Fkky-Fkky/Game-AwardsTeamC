#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Damage : public BossAttack {
public:
	Damage() {}
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void Ready();
	void Attack(Boss* boss);
	void BeatR(Boss* boss);
	void BeatL(Boss* boss);
	void Reset();
	void HandReturn();
};