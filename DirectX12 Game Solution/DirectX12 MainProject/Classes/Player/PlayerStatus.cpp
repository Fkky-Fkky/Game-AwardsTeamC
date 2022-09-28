#include "Classes/Player/PlayerStatus.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief �l�̏�����
*/
void player::PlayerStatus::Initialize() {
	hp_ = PLAYER_HP_MAX_;
	invincible_time_ = 0.0f;
	damage_ = 0.0f;
	is_invincible_ = false;
}

/**
* @brief HP�̍X�V
* 
* @param[in] deltaTime ����
* @param[in] obj_m �I�u�W�F�N�g�}�l�[�W���[
*/
void player::PlayerStatus::Update(const float deltatime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltatime, 0.0f);
	if (invincible_time_ <= 0.0f) {
		is_invincible_ = false;
	}

	if (obj_m->IsPlayerDmg() && !is_invincible_) {
		is_invincible_ = true;
		if (obj_m->IsBossHandOpen()) {
			damage_ = OPEN_DAMAGE_;
		}
		else {
			damage_ = CLOSE_DAMAGE_;
		}
		DamageProcess();
	}
}

/**
* @brief �v���C���[�̃_���[�W����
*/
void player::PlayerStatus::DamageProcess() {
	hp_ -= damage_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}