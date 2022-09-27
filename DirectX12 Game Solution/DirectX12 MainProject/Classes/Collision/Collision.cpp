#include "Classes/Collision/Collision.h"
#include "Classes/Object/ObjectManager.h"

void Collision::Initialize() {
	hand_dmg_flag_reset_time_ = 0.0f;
	player_dmg_flag_r_ = false;
	player_dmg_flag_l_ = false;
	boss_body_dmg_flg_	  = false;
	boss_hand_r_dmg_flag_ = false;
	boss_hand_l_dmg_flag_ = false;
}

void Collision::Update(const float deltaTime, const ObjectManager* const obj_m_) {
	bool is_boss_r_atk_ = obj_m_->IsBossRAttack();
	bool is_boss_l_atk_ = obj_m_->IsBossLAttack();
	bool is_player_atk_ = obj_m_->GetPlayerAttackFlag();
	BoundingOrientedBox player_col_		 = obj_m_->GetPlayerCollision();
	BoundingOrientedBox player_atk_col_	 = obj_m_->GetPlayerAttackCollision();
	BoundingOrientedBox boss_body_col_	 = obj_m_->GetBossBodyCollision();
	BoundingOrientedBox boss_r_hand_col_ = obj_m_->GetBossRHandCollision();
	BoundingOrientedBox boss_l_hand_col_ = obj_m_->GetBossLHandCollision();


	if (is_boss_r_atk_) {	//プレイヤー:ボス攻撃の判定
		player_dmg_flag_r_ = player_col_.Intersects(boss_r_hand_col_);
	}
	else {
		player_dmg_flag_r_ = false;
	}

	if (is_boss_l_atk_) {
		player_dmg_flag_l_ = player_col_.Intersects(boss_l_hand_col_);
	}
	else {
		player_dmg_flag_l_ = false;
	}
	
	if (is_player_atk_) {	//プレイヤー攻撃:ボス頭の判定
		boss_body_dmg_flg_ = player_atk_col_.Intersects(boss_body_col_);
	}
	else {
		boss_body_dmg_flg_ = false;
	}

	if (is_player_atk_) {	//プレイヤー攻撃:ボス手の判定
		boss_hand_r_dmg_flag_ = player_atk_col_.Intersects(boss_r_hand_col_);
		boss_hand_l_dmg_flag_ = player_atk_col_.Intersects(boss_l_hand_col_);
		hand_dmg_flag_reset_time_ = 0.1f;
	}

	hand_dmg_flag_reset_time_ = std::max(hand_dmg_flag_reset_time_ - deltaTime, 0.0f);
	if (hand_dmg_flag_reset_time_ <= 0.0f) {	//一定時間経過で手のダメージフラグ降ろす
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
	}
}