#include "Classes/Enemy/Boss/Boss.h"

Boss::Boss() {
	body_pos   = SimpleMath::Vector3::Zero;
	r_hand_pos = SimpleMath::Vector3::Zero;
	l_hand_pos = SimpleMath::Vector3::Zero;

	time_delta = 0.0f;
	speed = 0.0f;
	slap_time = 0.0f;
	boss_state = 0;
}

void Boss::Intialize() {
	r_hand_rote = SimpleMath::Vector3(-30.0f, 5.0f, 0.0f);
	speed = 0.0f;
	boss_state = WAIT;
	slap_time = 0.0f;
}

void Boss::LoadAseets(){
	boss_body = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss.X");
	/*boss_body->SetScale(0.1f);*/
	body_pos = SimpleMath::Vector3(0.0f, -30.0f, 80.0f);

	right_hand = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_hand_R.X");
	r_hand_pos = SimpleMath::Vector3(-80.0f, 30.0f, 80.0f);
	

	left_hand = DX9::Model::CreateFromFile(DXTK->Device9, L"Boss/boss_hand_L.X");
	l_hand_pos = SimpleMath::Vector3(80.0f, 30.0f, 80.0f);

}

void Boss::Update(const float deltaTime) {
	time_delta = deltaTime;
	if (DXTK->KeyState->Right) {
		r_hand_rote.y += 10.0f * deltaTime;
	}
	if (DXTK->KeyState->Left) {
		r_hand_rote.y -= 10.0f * deltaTime;
	}
	if (DXTK->KeyState->Up) {
		r_hand_rote.x += 10.0f * deltaTime;
	}
	if (DXTK->KeyState->Down) {
		r_hand_rote.x -= 10.0f * deltaTime;
	}

	if (DXTK->KeyEvent->pressed.Enter) {
		boss_state = RIGHT_SLAP;
	}

	if (DXTK->KeyEvent->pressed.Back) {
		boss_state = LEFT_SLAP;
	}

	Attack();

}

void Boss::Render(){
	boss_body->SetPosition(body_pos);
	boss_body->Draw();

	right_hand->SetPosition(r_hand_pos);
	right_hand->SetRotation(r_hand_rote);
	right_hand->Draw();

	left_hand->SetPosition(l_hand_pos);
	left_hand->SetRotation(SimpleMath::Vector3(-30.0f, -5.0f, 0.0f));
	left_hand->Draw();
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
	}
}

void Boss::RightSlap() {
	//speed = std::min(speed + 500.0f * time_delta, 10000.0f);
	//if(!flag)
	//	r_hand_pos.x -= speed * time_delta;
	//else
	//	r_hand_pos.x += speed * time_delta;

	//if (r_hand_pos.x <= -150.0f)
	//	flag = true;

	slap_time += time_delta;
	r_hand_pos.x -= V0 * slap_time - 0.5f * GRAVITY * slap_time * slap_time;

	if (r_hand_pos.x >= 200.0f) {
		r_hand_pos.x = -80.0f;
		slap_time = 0.0f;
		boss_state = WAIT;
	}
}

void Boss::LeftSlap() {

	slap_time += time_delta;
	l_hand_pos.x += V0 * slap_time - 0.5f * GRAVITY * slap_time * slap_time;


	if (l_hand_pos.x <= -200.0f) {
		l_hand_pos.x = 80.0f;
		speed = 0.0f;
		slap_time = 0.0f;
		boss_state = WAIT;
	}
}