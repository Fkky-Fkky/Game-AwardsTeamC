#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Boss.h"

void Wait::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	if (wait_time_ < max_wait_time) {
		wait_time_ += deltaTime;
	}
	else {
		wait_time_ = 0.0f;
		boss->RandomAttackState();
	}
}