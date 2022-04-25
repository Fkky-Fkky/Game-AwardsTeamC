#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossHandMove.h"

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_l.Initialize();
	hand_r.Initialize();
	attack = new BossHandMove;
	attack->Initialize(&hand_l, &hand_r);
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
	attack->Update(deltaTime);
}

void Boss::Render(){
	body.Render();
	core.Render();
	hand_l.Render();
	hand_r.Render();
}