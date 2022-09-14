#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Death.h"
#include "Classes/Collision/ObjectManager.h"

void HandManager::Initialize() {
	hand_l.Initialize();
	hand_r.Initialize();
	attack = new boss::Wait;
	attack->Initialize(&hand_l, &hand_r);
	std::random_device seed;
	random_engine_	  = std::mt19937(seed());
	random_atk_dist_  = std::uniform_int_distribution<>(ATTACK_STATE_MIN_, ATTACK_STATE_MAX_);
	random_hand_dist_ = std::uniform_int_distribution<>(ROCK, PAPER);
	
	slap_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Slap.wav");
	beat_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Beat.wav");

	attack_state_ = WAIT;
	boss_hp_	  = 0.0f;
	hand_state_		= ROCK;
	old_hand_state_ = PAPER;
	action_end_flag_	   = false;
	is_switch_weak_state_ = false;
	same_handstate_flag_   = false;
}

void HandManager::LoadAssets() {
	hand_l.LoadAssets();
	hand_r.LoadAssets();
	beat_effect_ = DX12Effect.Create(L"Effect/Eff_shock/Eff_shock.efk");
}

void HandManager::Update(const float deltaTime, const ObjectManager* const obj_m) {
	boss_hp_ = obj_m->GetBossHP();
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
	attack->Update(deltaTime, obj_m, this);
	SwitchStateWait();
	if (obj_m->IsBossWeak() && !is_switch_weak_state_) {
		is_switch_weak_state_ = true;
		SwitchStateWeak();
	}

	if (boss_hp_ <= 0.0f) {
		SwitchStateDeath();
	}
}

void HandManager::Render()const {
	hand_l.Render();
	hand_r.Render();
}

void HandManager::RandomAttackState() {	//ボスのHPに比例して攻撃の種類変化
	int random_state_max_ = ATTACK_STATE_MAX_;
	int old_atk_state_	  = attack_state_;
	bool normal_mode_	  = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_mode_		  = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

	if (normal_mode_) {	//ボスHP3/3
		random_state_max_ = NORMAL_MODE_MAX_;
	}
	else if (hard_mode_) {	//ボスHP2/3
		random_state_max_ = HARD_MODE_MAX_;
	}

	random_atk_dist_ = std::uniform_int_distribution<>(ATTACK_STATE_MIN_, random_state_max_);

	while (true) {
		attack_state_ = random_atk_dist_(random_engine_);
		if (attack_state_ != old_atk_state_) {
			break;
		}
	}

	SwitchStateAttack();
}

void HandManager::RandomHandState() {	//手の状態を変更する(グー・パー)
	if (same_handstate_flag_) {	//2連続同じ状態だった場合もう片方の状態にする
		hand_state_ = (old_hand_state_ == ROCK) ? PAPER : ROCK;
		same_handstate_flag_ = false;
	}
	else {
		hand_state_ = random_hand_dist_(random_engine_);
	}

	if (attack_state_ == BEAT_RUSH_R) {	//連続叩きつけ攻撃のみグーに固定する
		hand_state_ = ROCK;
	}

	if (hand_state_ == old_hand_state_) {
		same_handstate_flag_ = true;
	}

	old_hand_state_ = hand_state_;
}

void HandManager::SwitchStateAttack() {	//ボスの攻撃変更
	delete attack;
	attack_state_ = RIGHT_BEAT;
	switch (attack_state_) {
	case LEFT_BEAT:		attack = new boss::LeftBeat;	break;
	case LEFT_SLAP:		attack = new boss::LeftSlap;	break;
	case RIGHT_BEAT:	attack = new boss::RightBeat;	break;
	case RIGHT_SLAP:	attack = new boss::RightSlap;	break;
	case DOUBLE_SLAP:	attack = new boss::DoubleSlap;	break;
	case BEAT_RUSH_R:	attack = new boss::BeatRushR;	break;
	}
	attack->Initialize(&hand_l, &hand_r);
	RandomHandState();
}

void HandManager::SwitchStateWait() {	//待機状態に切り替え
	if (action_end_flag_) {
		delete attack;
		attack = new boss::Wait;
		attack->Initialize(&hand_l, &hand_r);
		action_end_flag_ = false;
	}
}

void HandManager::SwitchStateWeak() {	//ウィーク状態に切り替え
	delete attack;
	attack = new boss::Weak;
	attack->Initialize(&hand_l, &hand_r);
}

void HandManager::SwitchStateDeath() {
	if (!is_switch_state_death_) {
		is_switch_state_death_ = true;
		delete attack;
		attack = new boss::Death;
		attack->Initialize(&hand_l, &hand_r);
	}
}

void HandManager::PlaySlapSE() const {
	slap_se_->Play();
}

void HandManager::PlayBeatSE() const {
	beat_se_->Play();
}

void HandManager::PlayBeatEffect(const SimpleMath::Vector3 effect_pos) const {
	DX12Effect.Play(beat_effect_, effect_pos);
}

void HandManager::ActionEnd() {
	action_end_flag_ = true;
	is_switch_weak_state_ = false;
}