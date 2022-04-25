#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"
#include <Bezier.h>

BossHand::BossHand() {
	bezier_t = 0.0f;
	boss_state = 0;
	time_delta = 0.0f;
	wait_time = 0.0f;
}

void BossHand::Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote) {
	BossParts::Initialize(pos, rote);
	bezier_t = 0.0f;

	boss_state = WAIT;
	time_delta = 0.0f;

	std::random_device seed;
	randomEngine = std::mt19937(seed());
	randomDist = std::uniform_int_distribution<>(1, 4);
	wait_time = 0.0f;

	player_pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
}

void BossHand::LoadAssets(LPCWSTR file_name){
	BossParts::LoadAssets(file_name);
	collision = model->GetBoundingOrientedBox();
	collision.Extents = SimpleMath::Vector3(collision.Extents);

	collision_model = DX9::Model::CreateBox(
		DXTK->Device9,
		collision.Extents.x,
		collision.Extents.y,
		collision.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	collision_model->SetMaterial(material);

	model->SetScale(2.0f);
}

void BossHand::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {

	time_delta = deltaTime;

	player_pos_ = player_pos;
	//if (DXTK->KeyEvent->pressed.Enter) {
	//	boss_state = RIGHT_SLAP;
	//}
	//if (DXTK->KeyEvent->pressed.Back) {
	//	boss_state = LEFT_SLAP;
	//}
	//if (DXTK->KeyEvent->pressed.Space) {
	//	boss_state = RIGHT_BEAT;
	//}
	//if (DXTK->KeyState->E) {
	//	boss_state = LEFT_BEAT;
	//}
	//if (DXTK->KeyEvent->pressed.P) {
	//	boss_state = -1;
	//}

	//Attack();
	//RandomAction();

	collision.Center = model->GetPosition();
	collision.Orientation = model->GetRotationQuaternion();

}

void BossHand::Render(){
	BossParts::Render();
	collision_model->SetPosition(collision.Center);
	collision_model->SetRotationQuaternion(collision.Orientation);
	collision_model->Draw();
}

//void BossHand::Attack() {
//	switch (boss_state) {
//	case WAIT:
//		break;
//
//	case RIGHT_SLAP:
//		hand_r.RightSlap(this);
//		break;
//
//	case LEFT_SLAP:
//		hand_l.LeftSlap(this);
//		break;
//
//	case RIGHT_BEAT:
//		hand_r.RightBeat(this);
//		break;
//
//	case LEFT_BEAT:
//		hand_l.LeftBeat(this, player_pos_);
//		break;
//	}
//}

//void BossHand::RandomAction() {
//	if (boss_state == WAIT) {
//		wait_time += time_delta;
//	}
//
//	if(wait_time >= 3.0f){
//		boss_state = randomDist(randomEngine);
//		wait_time = 0.0f;
//	}
//}

//void BossAttack::SusiZanmai() {
//	r_hand_pos = Bezier::CubicInterpolate(
//		SimpleMath::Vector3(-80.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(100.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-50.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-100.0f, -40.0f, 80.0f),
//		bezier_t
//	);
//	l_hand_pos = Bezier::CubicInterpolate(
//		SimpleMath::Vector3(80.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(-100.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(50.0f, 30.0f, 80.0f),
//		SimpleMath::Vector3(100.0f, -40.0f, 80.0f),
//		bezier_t
//	);
//	r_hand_rote.x += 1.0f * time_delta;
//	if (r_hand_rote.x >= -28.0f) {
//		r_hand_rote.x = -28.0f;
//	}
//
//	l_hand_rote.x += 1.0f * time_delta;
//	if (l_hand_rote.x >= -28.0f) {
//		l_hand_rote.x = -28.0f;
//	}
//
//	bezier_t += 1.0f / 1.5f * time_delta;//1.5•b‚©‚¯‚ÄƒS[ƒ‹‚ÉŒü‚©‚¤
//	if (r_hand_pos.y <= -40.0f) {
//		bezier_t = 0.0f;
//		boss_state = WAIT;
//	}
//}