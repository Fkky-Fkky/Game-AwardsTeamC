#include "Classes/Enemy/Boss/Parts/Hands/Attack/Advent.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"

/**
* @brief ��̍~�Տ����X�V
* 
* @param[in] deltaTIme ����
* @oaram[in] obj_m �I�u�W�F�N�g�}�l�[�W���[
* @oaram[out] act_m �A�N�V�����}�l�[�W���[
*/
void boss::Advent::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	l_pos_ = boss_handL_->GetHandPos();
	r_pos_ = boss_handR_->GetHandPos();
	l_rot_ = boss_handL_->GetRotation();
	r_rot_ = boss_handR_->GetRotation();

	time_delta_ = deltaTime;
	switch (advent_state_) {
	case ADVENT_ACTION:	AdventAction();		break;
	case ACTION_END:	act_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handR_->SetHandRote(r_rot_);
	boss_handL_->SetHandRote(l_rot_);
}

/**
* @brief ����~�Ղ�����
*/
void boss::Advent::AdventAction() {
	l_pos_.y = std::max(l_pos_.y - MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	r_pos_.y = std::max(r_pos_.y - MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);

	const bool is_init_pos_ = l_pos_.y <= HAND_INITIAL_POS_Y_ && r_pos_.y <= HAND_INITIAL_POS_Y_;
	if (is_init_pos_) {
		advent_state_ = ACTION_END;
	}
}