#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"

void Wait::Update(const float deltaTime, SimpleMath::Vector3 player_pos, bool& attack_flag) {
	if (wait_time < max_wait_time) {
		wait_time += deltaTime;
	}
	else {
		attack_flag = false;
		wait_time = 0.0f;
	}
}