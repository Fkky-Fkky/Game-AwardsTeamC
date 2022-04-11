#include "Classes/Enemy/Boss/BossAttack.h"
#include <Bezier.h>

BossAttack::BossAttack() {
	slap_time = 0.0f;
	beat_time = 0.0f;
	bezier_t = 0.0f;
	hand_return_flag = false;

	r_hand_pos = SimpleMath::Vector3::Zero;
	l_hand_pos = SimpleMath::Vector3::Zero;

	boss_state = 0;
	hit_flag = false;
	time_delta = 0.0f;
}

void BossAttack::Intialize() {
	r_hand_rote = SimpleMath::Vector3(-30.0f, 5.0f, 0.0f);
	l_hand_rote = SimpleMath::Vector3(-30.0f, -5.0f, 0.0f);

	slap_time = 0.0f;
	beat_time = 0.0f;
	bezier_t = 0.0f;
	hand_return_flag = false;

	boss_state = WAIT;
	hit_flag = false;
	time_delta = 0.0f;
}

void BossAttack::LoadAseets() {
	right_hand = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_hand_R.X");
	r_hand_pos = SimpleMath::Vector3(-80.0f, 30.0f, 80.0f);

	right_hand_obb = right_hand->GetBoundingOrientedBox();
	right_hand_obb.Extents = SimpleMath::Vector3(right_hand_obb.Extents) * 0.2f;

	right_hand_obb_model = DX9::Model::CreateBox(
		DXTK->Device9,
		right_hand_obb.Extents.x,
		right_hand_obb.Extents.y,
		right_hand_obb.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(1.0f, 0.0f, 0.0f, 0.75f);
	right_hand_obb_model->SetMaterial(material);


	left_hand = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_hand_L.X");
	l_hand_pos = SimpleMath::Vector3(80.0f, 30.0f, 80.0f);

	left_hand_obb = left_hand->GetBoundingOrientedBox();
	left_hand_obb.Extents = SimpleMath::Vector3(left_hand_obb.Extents) * 0.2f;

	left_hand_obb_model = DX9::Model::CreateBox(
		DXTK->Device9,
		left_hand_obb.Extents.x,
		left_hand_obb.Extents.y,
		left_hand_obb.Extents.z
	);
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	left_hand_obb_model->SetMaterial(material);

}

void BossAttack::Update(const float deltaTime) {
	time_delta = deltaTime;

	if (DXTK->KeyState->Right) {
		//r_hand_rote.y += 5.0f * deltaTime;
		r_hand_pos.x += 40.0f * deltaTime;
	}
	if (DXTK->KeyState->Left) {
		//r_hand_rote.y -= 5.0f * deltaTime;
		r_hand_pos.x -= 40.0f * deltaTime;
	}
	if (DXTK->KeyState->Up) {
		r_hand_rote.x += 5.0f * deltaTime;
	}
	if (DXTK->KeyState->Down) {
		r_hand_rote.x -= 5.0f * deltaTime;
	}

	if (DXTK->KeyEvent->pressed.Enter) {
		boss_state = RIGHT_SLAP;
	}

	if (DXTK->KeyEvent->pressed.Back) {
		boss_state = LEFT_SLAP;
	}

	if (DXTK->KeyEvent->pressed.Space) {
		boss_state = RIGHT_BEAT;
	}

	if (DXTK->KeyState->E) {
		boss_state = LEFT_BEAT;
	}

	if (DXTK->KeyEvent->pressed.P) {
		boss_state = -1;
	}

	Attack();

	hit_flag = right_hand_obb.Intersects(left_hand_obb);


	right_hand_obb.Center = right_hand->GetPosition();
	right_hand_obb.Orientation = right_hand->GetRotationQuaternion();

	left_hand_obb.Center = left_hand->GetPosition();
	left_hand_obb.Orientation = left_hand->GetRotationQuaternion();

}

void BossAttack::Render() {
	right_hand->SetPosition(r_hand_pos);
	right_hand->SetRotation(r_hand_rote);
	right_hand->Draw();

	right_hand_obb_model->SetPosition(right_hand_obb.Center);
	right_hand_obb_model->SetRotationQuaternion(right_hand_obb.Orientation);
	right_hand_obb_model->Draw();

	left_hand->SetPosition(l_hand_pos);
	left_hand->SetRotation(l_hand_rote);
	left_hand->Draw();

	left_hand_obb_model->SetPosition(left_hand_obb.Center);
	left_hand_obb_model->SetRotationQuaternion(left_hand_obb.Orientation);
	left_hand_obb_model->Draw();
}


void BossAttack::Attack() {
	switch (boss_state) {
	case WAIT:
		break;

	case RIGHT_SLAP:
		RightSlap();
		break;

	case LEFT_SLAP:
		LeftSlap();
		break;

	case RIGHT_BEAT:
		RightBeat();
		break;

	case LEFT_BEAT:
		LeftBeat();
		break;

	default:
		r_hand_pos.y = 30.0f;
		break;
	}
}

void BossAttack::RightSlap() {
	slap_time += time_delta;
	r_hand_pos.x -= SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;

	if (r_hand_pos.x >= 300.0f) {
		r_hand_pos.x = -300.0f;
		hand_return_flag = true;
	}

	if (r_hand_pos.x >= -80.0f && hand_return_flag) {
		r_hand_pos.x = -80.0f;
		slap_time = 0.0f;
		hand_return_flag = false;
		boss_state = WAIT;
	}
}

void BossAttack::LeftSlap() {
	slap_time += time_delta;
	l_hand_pos.x += SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;

	if (l_hand_pos.x <= -300.0f) {
		l_hand_pos.x = 300.0f;
		hand_return_flag = true;
	}

	if (l_hand_pos.x <= 80.0f && hand_return_flag) {
		l_hand_pos.x = 80.0f;
		slap_time = 0.0f;
		hand_return_flag = false;
		boss_state = WAIT;
	}
}

void BossAttack::RightBeat() {
	beat_time += time_delta;
	r_hand_rote.x -= 2.0f * time_delta;
	if (r_hand_rote.x <= -31.5f) {
		r_hand_rote.x = -31.5f;
	}

	r_hand_pos.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;

	if (r_hand_pos.y <= -30.0f) {
		r_hand_pos.y = -30.0f;
		beat_time = 0.0f;
		boss_state = WAIT;
	}
}
void BossAttack::LeftBeat() {
	beat_time += time_delta;
	l_hand_rote.x -= 2.0f * time_delta;
	if (l_hand_rote.x <= -31.5f) {
		l_hand_rote.x = -31.5f;
	}

	l_hand_pos.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;

	if (l_hand_pos.y <= -30.0f) {
		l_hand_pos.y = -30.0f;
		beat_time = 0.0f;
		boss_state = WAIT;
	}
}

void BossAttack::SusiZanmai() {
	r_hand_pos = Bezier::CubicInterpolate(
		SimpleMath::Vector3(-80.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(100.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(-50.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(-100.0f, -40.0f, 80.0f),
		bezier_t
	);
	l_hand_pos = Bezier::CubicInterpolate(
		SimpleMath::Vector3(80.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(-100.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(50.0f, 30.0f, 80.0f),
		SimpleMath::Vector3(100.0f, -40.0f, 80.0f),
		bezier_t
	);
	r_hand_rote.x += 1.0f * time_delta;
	if (r_hand_rote.x >= -28.0f) {
		r_hand_rote.x = -28.0f;
	}

	l_hand_rote.x += 1.0f * time_delta;
	if (l_hand_rote.x >= -28.0f) {
		l_hand_rote.x = -28.0f;
	}

	bezier_t += 1.0f / 1.5f * time_delta;//1.5•b‚©‚¯‚ÄƒS[ƒ‹‚ÉŒü‚©‚¤
	if (r_hand_pos.y <= -40.0f) {
		bezier_t = 0.0f;
		boss_state = WAIT;
	}
}