#include "Classes/Enemy/Boss/Parts/Hands/Attack/Damage.h"
#include "Classes/Collision/ObjectManager.h"
#include "Classes/Enemy/Boss/Boss.h"

void Damage::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) {
	pos_r_ = boss_handR_->GetHandPos();
	rot_r_ = boss_handR_->GetRotation();
	pos_l_ = boss_handL_->GetHandPos();
	rot_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (damage_state_) {
	case DAMAGE:			HandDamage(obj_m);	break;
	case WAIT:				Wait();				break;
	case OFF_SCREEN_MOVE:	OffScreenMove();	break;
	case RESET:				Reset();			break;
	case INITIAL_POS_MOVE:  InitialPosMove();	break;
	case ACTION_END:		boss->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handR_->SetHandRote(rot_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handL_->SetHandRote(rot_l_);
}

void Damage::HandDamage(ObjectManager* obj_m) {	//手にダメージを与える
	if (obj_m->IsBossHandRDmg()) {
		boss_handR_->HandDamageProcess();
	}
	if (obj_m->IsBossHandLDmg()) {
		boss_handL_->HandDamageProcess();
	}
	damage_state_ = WAIT;
}

void Damage::Wait() {
	wait_time_ += time_delta_;
	if (wait_time_ > 0.5f) {
		damage_state_ = OFF_SCREEN_MOVE;
	}
}

void Damage::OffScreenMove() {	//手を画面外に移動する
	pos_r_.x = std::max(pos_r_.x - MOVE_SPEED_X_ * time_delta_, -HAND_RETURN_POS_X_);
	pos_l_.x = std::min(pos_l_.x + MOVE_SPEED_X_ * time_delta_,  HAND_RETURN_POS_X_);

	if (pos_r_.x <= -HAND_RETURN_POS_X_ &&
		pos_l_.x >=  HAND_RETURN_POS_X_) {
		damage_state_ = RESET;
	}
}

void Damage::Reset() {	//X座標以外を初期位置にする
	pos_r_.y = HAND_INITIAL_POS_Y_;
	pos_r_.z = HAND_INITIAL_POS_Z_;
	pos_l_.y = HAND_INITIAL_POS_Y_;
	pos_l_.z = HAND_INITIAL_POS_Z_;
	rot_r_.x = XM_PIDIV4;
	rot_l_.x = XM_PIDIV4;
	damage_state_ = INITIAL_POS_MOVE;
}

void Damage::InitialPosMove() {	//手を初期位置へ移動
	pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	if (pos_r_.x >= HAND_R_INITIAL_POS_X_ &&
		pos_l_.x <= HAND_L_INITIAL_POS_X_) {
		damage_state_ = ACTION_END;
	}
}