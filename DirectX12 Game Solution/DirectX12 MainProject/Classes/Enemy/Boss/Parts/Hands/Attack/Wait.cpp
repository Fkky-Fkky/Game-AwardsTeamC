#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Boss.h"

void Wait::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	if (wait_time < max_wait_time) {
		wait_time += deltaTime;
	}
	else {
		wait_time = 0.0f;
		boss->RandomAttackState();
	}
}