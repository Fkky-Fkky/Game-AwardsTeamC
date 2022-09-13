#include "Classes/Collision/Collision.h"
#include "Classes/Collision/ObjectManager.h"

void Collision::Initialize() {
	hand_dmg_flag_reset_time_ = 0.0f;
	player_dmg_flag_r_ = false;
	player_dmg_flag_l_ = false;
	boss_body_dmg_flg_	  = false;
	boss_hand_r_dmg_flag_ = false;
	boss_hand_l_dmg_flag_ = false;
}

void Collision::LoadAssets() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Collision::Update(const float deltaTime, const ObjectManager* const obj_m_) {
	bool boss_r_atk_flag_ = obj_m_->GetBossRAttackFlag();
	bool boss_l_atk_flag_ = obj_m_->GetBossLAttackFlag();
	bool player_atk_flag_ = obj_m_->GetPlayerAttackFlag();
	bool player_invincible_flag = obj_m_->IsPlayerInvincible();
	BoundingOrientedBox player_col_		 = obj_m_->GetPlayerCollision();
	BoundingOrientedBox player_atk_col_	 = obj_m_->GetPlayerAttackCollision();
	BoundingOrientedBox boss_body_col_	 = obj_m_->GetBossBodyCollision();
	BoundingOrientedBox boss_r_hand_col_ = obj_m_->GetBossRHandCollision();
	BoundingOrientedBox boss_l_hand_col_ = obj_m_->GetBossLHandCollision();


	if (!player_invincible_flag) {	//プレイヤー:ボス攻撃の判定
		if (boss_r_atk_flag_) {
			player_dmg_flag_r_ = player_col_.Intersects(boss_r_hand_col_);
		}
		else {
			player_dmg_flag_r_ = false;
		}

		if (boss_l_atk_flag_) {
			player_dmg_flag_l_ = player_col_.Intersects(boss_l_hand_col_);
		}
		else {
			player_dmg_flag_l_ = false;
		}
	}
	
	if (player_atk_flag_) {	//プレイヤー攻撃:ボス頭の判定
		boss_body_dmg_flg_ = player_atk_col_.Intersects(boss_body_col_);
	}
	else {
		boss_body_dmg_flg_ = false;
	}

	if (player_atk_flag_) {	//プレイヤー攻撃:ボス手の判定
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

void Collision::Render2D() const {
	if (player_dmg_flag_r_ ||
		player_dmg_flag_l_) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"当たってる"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"当たってない"
		);
	}

	if (boss_hand_r_dmg_flag_ ||
		boss_hand_l_dmg_flag_) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 90.0f),
			DX9::Colors::Red,
			L"手に攻撃当たってる"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 90.0f),
			DX9::Colors::Red,
			L"手に攻撃当たってない"
		);
	}
}