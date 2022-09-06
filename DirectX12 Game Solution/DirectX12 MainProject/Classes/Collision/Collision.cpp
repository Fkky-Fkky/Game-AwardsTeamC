#include "Classes/Collision/Collision.h"
#include "Classes/Collision/ObjectManager.h"

void Collision::Initialize() {
	hand_dmg_flag_reset_time_ = 0.0f;
	player_dmg_flag_r_ = false;
	player_dmg_flag_l_ = false;
	boss_core_dmg_flg_	  = false;
	boss_hand_r_dmg_flag_ = false;
	boss_hand_l_dmg_flag_ = false;
	is_boss_hand_open_	  = false;
}

void Collision::LoadAssets() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Collision::Update(const float deltaTime, ObjectManager* obj_m_) {
	bool boss_r_atk_flag_ = obj_m_->GetBossRAttackFlag();
	bool boss_l_atk_flag_ = obj_m_->GetBossLAttackFlag();
	bool player_atk_flag_ = obj_m_->GetPlayerAttackFlag();
	bool player_invincible_flag = obj_m_->IsPlayerInvincible();
	BoundingOrientedBox player_col_		 = obj_m_->GetPlayerCollision();
	BoundingOrientedBox player_atk_col_	 = obj_m_->GetPlayerAttackCollision();
	BoundingOrientedBox boss_core_col_	 = obj_m_->GetBossCoreCollision();
	BoundingOrientedBox boss_r_hand_col_ = obj_m_->GetBossRHandCollision();
	BoundingOrientedBox boss_l_hand_col_ = obj_m_->GetBossLHandCollision();

	is_boss_hand_open_ = obj_m_->IsBossHandOpen();

	if (!player_invincible_flag) {	//�v���C���[:�{�X�U���̔���
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
	
	if (player_atk_flag_) {	//�v���C���[�U��:�{�X�R�A�̔���
		boss_core_dmg_flg_ = player_atk_col_.Intersects(boss_core_col_);
	}
	else {
		boss_core_dmg_flg_ = false;
	}

	if (is_boss_hand_open_) {	//�v���C���[�U��:�{�X��̔���
		if (player_atk_flag_) {
			boss_hand_r_dmg_flag_ = player_atk_col_.Intersects(boss_r_hand_col_);
			boss_hand_l_dmg_flag_ = player_atk_col_.Intersects(boss_l_hand_col_);
			hand_dmg_flag_reset_time_ = 0.1f;
		}
	}
	hand_dmg_flag_reset_time_ = std::max(hand_dmg_flag_reset_time_ - deltaTime, 0.0f);
	if (hand_dmg_flag_reset_time_ <= 0.0f) {	//��莞�Ԍo�߂Ń_���[�W�t���O�~�낷
		boss_hand_r_dmg_flag_ = false;
		boss_hand_l_dmg_flag_ = false;
	}
}

void Collision::Render2D() {
	if (player_dmg_flag_r_ ||
		player_dmg_flag_l_) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"�������Ă�"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"�������ĂȂ�"
		);
	}

	if (boss_hand_r_dmg_flag_ ||
		boss_hand_l_dmg_flag_) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 90.0f),
			DX9::Colors::Red,
			L"��ɍU���������Ă�"
		);
	}
	else {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 90.0f),
			DX9::Colors::Red,
			L"��ɍU���������ĂȂ�"
		);
	}

	if (is_boss_hand_open_) {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 120.0f),
			DX9::Colors::Red,
			L"�p�["
		);
	}
	else {
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 120.0f),
			DX9::Colors::Red,
			L"�O�["
		);
	}
}