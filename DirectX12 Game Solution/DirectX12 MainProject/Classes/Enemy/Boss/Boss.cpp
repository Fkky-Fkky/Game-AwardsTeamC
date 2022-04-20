#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Player/Player.h"

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_l.Initialize();
	hand_r.Initialize();
}

void Boss::LoadAseets(){
	body.LoadAssets();
	core.LoadAssets();
	hand_l.LoadAssets();
	hand_r.LoadAssets();
}

void Boss::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {
	hand_l.Update(deltaTime, player_pos);
	hand_r.Update(deltaTime, player_pos);
}

void Boss::Render(){
	body.Render();
	core.Render();
	hand_l.Render();
	hand_r.Render();
}