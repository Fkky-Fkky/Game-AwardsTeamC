#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Boss.h"

void Weak::Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss) {
	pos_r_ = boss_handR_->GetHandPos();
	pos_l_ = boss_handL_->GetHandPos();

	time_delta_ = deltaTime;
	switch (weak_state_) {
	case WEAK:			   BossWeak(boss);	  break;
	case HAND_HEAL:		   HandHeal();		  break;
	case INITIAL_POS_MOVE: InitialPosMove();  break;
	case ACTION_END:	   boss->ActionEnd(); break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handL_->SetHandPos(pos_l_);
}

void Weak::BossWeak(Boss* const boss) {	//ウィーク状態維持
	boss->SetWeakState(true);
	weak_time_ = std::min(weak_time_ + time_delta_, WEAK_TIME_MAX_);
	if (weak_time_ >= WEAK_TIME_MAX_) {
		boss->SetWeakState(false);
		weak_state_ = HAND_HEAL;
	}
}

void Weak::HandHeal() {	//手のHPを回復
	boss_handL_->HandHPHeal();
	boss_handR_->HandHPHeal();
	weak_state_ = INITIAL_POS_MOVE;
}

void Weak::InitialPosMove() {//手を初期座標に移動
	pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);

	if (pos_r_.x >= HAND_R_INITIAL_POS_X_ &&
		pos_l_.x <= HAND_L_INITIAL_POS_X_) {
		weak_state_ = ACTION_END;
	}
}