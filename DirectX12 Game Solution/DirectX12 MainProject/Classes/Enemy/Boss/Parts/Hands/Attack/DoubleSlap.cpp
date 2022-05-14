#include "DoubleSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

DoubleSlap::DoubleSlap() {
	r_pos_  = SimpleMath::Vector3::Zero;
	r_rote_ = SimpleMath::Vector3::Zero;
	l_pos_  = SimpleMath::Vector3::Zero;
	l_rote_ = SimpleMath::Vector3::Zero;

	action_state_ = 0;
	time_delta_ = 0.0f;
}

void DoubleSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss)	{
	r_pos_  = boss_handR_->GetHandPos();
	r_rote_ = boss_handR_->GetRotation();
	l_pos_  = boss_handL_->GetHandPos();
	l_rote_ = boss_handL_->GetRotation();

	switch (action_state_) {
	case READY:
		Ready();
		break;

	case ATTACK:
		Attack();
		break;

	case RESET:
		Reset();
		break;

	case ACTION_END:
		break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handR_->SetHandRote(r_rote_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handL_->SetHandRote(l_rote_);
}

void DoubleSlap::Ready() {

}

void DoubleSlap::Attack() {
	SlapR();
	SlapL();
}

void DoubleSlap::SlapR() {

}

void DoubleSlap::SlapL() {

}

void DoubleSlap::Reset() {

}