#include "Classes/Enemy/Boss/BossAttack.h"
#include <Bezier.h>

BossAttack::BossAttack() {
	slap_time = 0.0f;
	beat_time = 0.0f;
	bezier_t = 0.0f;
	hand_return_flag = false;

	l_hand_pos = SimpleMath::Vector3::Zero;

	boss_state = 0;
	hit_flag = false;
	time_delta = 0.0f;
}

void BossAttack::Initialize() {

	slap_time = 0.0f;
	beat_time = 0.0f;
	bezier_t = 0.0f;
	hand_return_flag = false;

	boss_state = WAIT;
	hit_flag = false;
	time_delta = 0.0f;
}

//void BossAttack::Update(const float deltaTime) {
//	time_delta = deltaTime;
//
//
//	if (DXTK->KeyEvent->pressed.Enter) {
//		boss_state = RIGHT_SLAP;
//	}
//
//	if (DXTK->KeyEvent->pressed.Back) {
//		boss_state = LEFT_SLAP;
//	}
//
//	if (DXTK->KeyEvent->pressed.Space) {
//		boss_state = RIGHT_BEAT;
//	}
//
//	if (DXTK->KeyState->E) {
//		boss_state = LEFT_BEAT;
//	}
//
//	if (DXTK->KeyEvent->pressed.P) {
//		boss_state = -1;
//	}
//
//	Attack();
//
//	//hit_flag = right_hand_obb.Intersects(left_hand_obb);
//}

//void BossAttack::Render() {
//	right_hand->SetPosition(r_hand_pos);
//	right_hand->SetRotation(r_hand_rote);
//	right_hand->Draw();
//
//	right_hand_obb_model->SetPosition(right_hand_obb.Center);
//	right_hand_obb_model->SetRotationQuaternion(right_hand_obb.Orientation);
//	right_hand_obb_model->Draw();
//
//	left_hand->SetPosition(l_hand_pos);
//	left_hand->SetRotation(l_hand_rote);
//	left_hand->Draw();
//
//	left_hand_obb_model->SetPosition(left_hand_obb.Center);
//	left_hand_obb_model->SetRotationQuaternion(left_hand_obb.Orientation);
//	left_hand_obb_model->Draw();
//}


//void BossAttack::Attack() {
//	switch (boss_state) {
//	case WAIT:
//		break;
//
//	case RIGHT_SLAP:
//		RightSlap();
//		break;
//
//	case LEFT_SLAP:
//		LeftSlap();
//		break;
//
//	case RIGHT_BEAT:
//		RightBeat();
//		break;
//
//	case LEFT_BEAT:
//		LeftBeat();
//		break;
//
//	default:
//		r_hand_pos.y = 30.0f;
//		break;
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