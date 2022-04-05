#include "Classes/Enemy/Boss/Boss.h"
#include <Bezier.h>

Boss::Boss() {
	body_pos   = SimpleMath::Vector3::Zero;
	r_hand_pos = SimpleMath::Vector3::Zero;
	l_hand_pos = SimpleMath::Vector3::Zero;

	time_delta = 0.0f;
	slap_time = 0.0f;
	boss_state = 0;
	hand_return_flag = false;
}

void Boss::Intialize() {
	r_hand_rote = SimpleMath::Vector3(-30.0f, 5.0f, 0.0f);
	l_hand_rote = SimpleMath::Vector3(-30.0f, -5.0f, 0.0f);
	boss_state = WAIT;
	slap_time = 0.0f;
	hand_return_flag = false;
	bezier_t = 0.0f;
	hit_flag = false;
}

void Boss::LoadAseets(){
	boss_body = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss.X");

	body_pos = SimpleMath::Vector3(0.0f, -30.0f, 80.0f);

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

	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Boss::Update(const float deltaTime) {
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
	Attack();


	right_hand_obb.Center = right_hand->GetPosition();
	right_hand_obb.Orientation = right_hand->GetRotationQuaternion();

	left_hand_obb.Center = left_hand->GetPosition();
	left_hand_obb.Orientation = left_hand->GetRotationQuaternion();

	
	hit_flag = right_hand_obb.Intersects(left_hand_obb);
	

}

void Boss::Render2D() {
	if (hit_flag)
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚è"
		);
	else
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"“–‚½‚ç‚È‚¢‚æ‚ÁI"
		);
}


void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();

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

void Boss::Attack() {
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
	}
}

void Boss::RightSlap() {
	slap_time += time_delta;
	r_hand_pos.x -= V0 * slap_time - HALF * GRAVITY * slap_time * slap_time;

	if (r_hand_pos.x >= 200.0f) {
		r_hand_pos.x = -200.0f;
		hand_return_flag = true;
	}

	if (r_hand_pos.x >= -80.0f && hand_return_flag) {
		r_hand_pos.x = -80.0f;
		slap_time = 0.0f;
		hand_return_flag = false;
		boss_state = WAIT;
	}
}

void Boss::LeftSlap() {
	slap_time += time_delta;
	l_hand_pos.x += V0 * slap_time - HALF * GRAVITY * slap_time * slap_time;

	if (l_hand_pos.x <= -200.0f) {
		l_hand_pos.x = 200.0f;
		hand_return_flag = true;
	}

	if (l_hand_pos.x <= 80.0f && hand_return_flag) {
		l_hand_pos.x = 80.0f;
		slap_time = 0.0f;
		hand_return_flag = false;
		boss_state = WAIT;
	}
}

void Boss::RightBeat() {
	//r_hand_pos.x += 20.0f * time_delta;
	//r_hand_pos.y += 1.0f*sinf(XMConvertToRadians(-90.0f));

}

void Boss::SusiZanmai() {
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