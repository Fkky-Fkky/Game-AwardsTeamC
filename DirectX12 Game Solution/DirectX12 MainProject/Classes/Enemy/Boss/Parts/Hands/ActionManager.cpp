#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Advent.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Death.h"

void ActionManager::Initialize() {
	hand_.Initialize();
	action_ = new boss::Advent;
	action_->Initialize(&hand_.GetHandL(), &hand_.GetHandR());
	std::random_device seed;
	random_engine_	 = std::mt19937(seed());
	random_atk_dist_ = std::uniform_int_distribution<>(ATTACK_STATE_MIN_, ATTACK_STATE_MAX_);

	attack_state_ = WAIT;
	action_end_flag_	= false;
	is_vertical_shake_  = false;
	is_side_shake_		= false;
	is_switch_state_weak_  = false;
	is_switch_state_death_ = false;
	is_hand_death_		   = false;

	slap_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Slap.wav");
	beat_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Beat.wav");
}

void ActionManager::LoadAssets() {
	hand_.LoadAssets();
	beat_effect_ = DX12Effect.Create(L"Effect/Eff_shock/Eff_shock.efk");
}

void ActionManager::Update(const float deltaTime, const ObjectManager* const obj_m) {
	boss_hp_ = obj_m->GetBossHP();

	hand_.Update(deltaTime);
	action_->Update(deltaTime, obj_m, this);
	SwitchStateWait();
	if (obj_m->IsBossWeak() && !is_switch_state_weak_) {
		is_switch_state_weak_ = true;
		SwitchStateWeak();
	}

	if (boss_hp_ <= 0.0f) {
		SwitchStateDeath();
	}
}

void ActionManager::Render() const {
	hand_.Render();
}

void ActionManager::RandomAttackState() {	//ボスのHPに比例して攻撃の種類変化
	int random_state_max_ = ATTACK_STATE_MAX_;
	int old_atk_state_	  = attack_state_;
	bool normal_mode_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_mode_	  = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

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

void ActionManager::SwitchStateAttack() {	//ボスの攻撃変更
	delete action_;
	switch (attack_state_) {
	case LEFT_BEAT:		action_ = new boss::LeftBeat;	break;
	case LEFT_SLAP:		action_ = new boss::LeftSlap;	break;
	case RIGHT_BEAT:	action_ = new boss::RightBeat;	break;
	case RIGHT_SLAP:	action_ = new boss::RightSlap;	break;
	case DOUBLE_SLAP:	action_ = new boss::DoubleSlap;	break;
	case BEAT_RUSH_R:	action_ = new boss::BeatRushR;	break;
	}
	action_->Initialize(&hand_.GetHandL(), &hand_.GetHandR());
	const bool IS_BEAT_RUSH_ = attack_state_ == BEAT_RUSH_R;
	hand_.RandomHandState(IS_BEAT_RUSH_);
}

void ActionManager::SwitchStateWait() {	//待機状態に切り替え
	if (action_end_flag_) {
		delete action_;
		action_ = new boss::Wait;
		action_->Initialize(&hand_.GetHandL(), &hand_.GetHandR());
		action_end_flag_ = false;
	}
}

void ActionManager::SwitchStateWeak() {	//ウィーク状態に切り替え
	delete action_;
	action_ = new boss::Weak;
	action_->Initialize(&hand_.GetHandL(), &hand_.GetHandR());
}

void ActionManager::SwitchStateDeath() {
	if (!is_switch_state_death_) {
		is_switch_state_death_ = true;
		delete action_;
		action_ = new boss::Death;
		action_->Initialize(&hand_.GetHandL(), &hand_.GetHandR());
	}
}

void ActionManager::ActionEnd() {
	action_end_flag_ = true;
	is_switch_state_weak_ = false;
}

void ActionManager::DeathActionEnd() {
	is_hand_death_ = true;
}

void ActionManager::PlaySlapSE() const {
	slap_se_->Play();
}

void ActionManager::PlayBeatSE() const {
	beat_se_->Play();
}

void ActionManager::PlayBeatEffect(const SimpleMath::Vector3 effect_pos) const {
	DX12Effect.Play(beat_effect_, effect_pos);
}