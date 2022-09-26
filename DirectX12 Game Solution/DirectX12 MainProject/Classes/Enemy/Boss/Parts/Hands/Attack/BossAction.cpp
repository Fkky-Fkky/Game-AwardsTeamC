#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"

/**
* @brief �l�̏�����
* 
* @param[out] boss_handL ����
* @param[out] boss_handR �E��
*/
void boss::BossAction::Initialize(BossHand* const boss_handL, BossHand* const boss_handR) {
	boss_handL_ = boss_handL;
	boss_handR_ = boss_handR;
	slap_speed_  = 0.0f;
	slap_y_time_ = 0.0f;
	is_se_play_	  = false;
	is_shake_set_ = false;
}

/**
* @brief �ガ�����U���̉��z�֐�
* 
* - �J�������c�h�ꂳ����
* - �ガ�����U���Ɏg�p����X�s�[�h���グ��
* - SE���Đ�����
* 
* @param[in] deltaTime ����
* @param[out] act_m �A�N�V�����}�l�[�W���[
*/
void boss::BossAction::SlapAttackBase(const float deltaTime, ActionManager* const act_m) {
	if (!is_shake_set_) {
		act_m->SetSideShake(true);
		is_shake_set_ = true;
	}
	slap_speed_ = std::min(slap_speed_ + ADD_SLAP_SPEED_ * deltaTime, SLAP_SPEED_MAX_X_);
	if (!is_se_play_) {
		act_m->PlaySlapSE();
		is_se_play_ = true;
	}
}

/**
* @brief �ガ�����U���\�����z�֐�
* 
* @param[in] deltaTime ����
* @return �\���̓���(���������グ)
*/
float boss::BossAction::SlapY(const float deltaTime) {
	slap_y_time_ += deltaTime;
	float r_slap_y_ = SLAP_SPEED_Y_ * slap_y_time_ - HALF_ * SLAP_GRAVITY_Y_ * slap_y_time_ * slap_y_time_;
	return r_slap_y_;
}