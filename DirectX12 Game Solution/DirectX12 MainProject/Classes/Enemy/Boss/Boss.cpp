#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Damage.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_l.Initialize();
	hand_r.Initialize();
	attack = new Wait;
	attack->Initialize(&hand_l, &hand_r);
	std::random_device seed;
	random_engine_	  = std::mt19937(seed());
	random_atk_dist_  = std::uniform_int_distribution<>(ATTACK_STATE_MIN_, ATTACK_STATE_MAX_);
	random_hand_dist_ = std::uniform_int_distribution<>(ROCK, PAPER);
	slap_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Slap.wav");
	beat_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Beat.wav");

	attack_state_	= WAIT;
	hand_state_		= ROCK;
	old_hand_state_ = PAPER;
	action_end_flag_	 = false;
	same_handstate_flag_ = false;
	hand_dmg_flag_		 = false;
	weak_state_start_flag_	 = false;
}

void Boss::LoadAseets() {
	body.LoadAssets();
	core.LoadAssets();
	hand_l.LoadAssets();
	hand_r.LoadAssets();
	beat_effect_ = DX12Effect.Create(L"Effect/Eff_shock/Eff_shock.efk");
}

void Boss::Update(const float deltaTime, ObjectManager* obj_m) {
	body.Update(deltaTime);
	core.Update(deltaTime, obj_m->GetBossDmgFlag(), this);
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
	attack->Update(deltaTime, obj_m, this);
	SwitchStateWait();
	if (obj_m->IsBossHandLDmg() ||
		obj_m->IsBossHandRDmg()) {
		SwitchStateDamage();
	}
	SwitchStateWeak();
}

void Boss::Render() {
	body.Render();
	core.Render();
	hand_l.Render();
	hand_r.Render();
}

void Boss::Render2D() {
	core.Render2D();
	hand_r.Render2D(0.0f);
	hand_l.Render2D(1000.0f);
}

void Boss::RandomAttackState() {	//ボスのHPに比例して攻撃の種類変化
	int boss_hp_ = GetBossHP();
	int random_state_max_ = ATTACK_STATE_MAX_;
	int old_atk_state_ = attack_state_;
	bool normal_mode_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_mode_   = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

	bool is_r_hand_broke_ = hand_r.GetHandHp() <= 0;	//右手が壊れているか
	bool is_l_hand_broke_ = hand_l.GetHandHp() <= 0;	//左手が壊れているか

	if (normal_mode_) {	//ボスHP3/3
		random_state_max_ = NORMAL_MODE_MAX_;
		if (is_l_hand_broke_) {	//左手のHPが0だった場合右手の攻撃のみ行う
			random_state_max_ = RIGHT_SLAP;
		}
		if (is_r_hand_broke_) {	//右手のHPが0だった場合左手の攻撃のみ行う
			random_state_max_ = LEFT_SLAP;
		}
	}
	else if (hard_mode_) {	//ボスHP2/3
		random_state_max_ = HARD_MODE_MAX_;
	}

	random_atk_dist_ = std::uniform_int_distribution<>(ATTACK_STATE_MIN_, random_state_max_);

	while (true) {
		attack_state_ = random_atk_dist_(random_engine_);
		bool is_l_hand_attack_ = attack_state_ == LEFT_BEAT  || attack_state_ == LEFT_SLAP;
		bool is_r_hand_attack_ = attack_state_ == RIGHT_BEAT || attack_state_ == RIGHT_SLAP;

		if (is_l_hand_broke_ && is_l_hand_attack_) {
			return;
		}
		if (is_r_hand_broke_ && is_r_hand_attack_) {
			return;
		}
		if (attack_state_ != old_atk_state_) {
			break;
		}
	}
	
	SwitchStateAttack();
}

void Boss::RandomHandState() {	//手の状態を変更する(グー・パー)
	if (same_handstate_flag_) {	//2連続同じ状態だった場合もう片方の状態にする
		hand_state_ = (old_hand_state_ == ROCK) ? PAPER : ROCK;
		same_handstate_flag_ = false;
	}
	else {
		hand_state_ = random_hand_dist_(random_engine_);
	}

	if (hand_state_ == old_hand_state_) {
		same_handstate_flag_ = true;
	}

	old_hand_state_ = hand_state_;
}

void Boss::SwitchStateAttack() {
	delete attack;
	switch (attack_state_) {
	case LEFT_BEAT:		attack = new LeftBeat;		break;
	case LEFT_SLAP:		attack = new LeftSlap;		break;
	case RIGHT_BEAT:	attack = new RightBeat;		break;
	case RIGHT_SLAP:	attack = new RightSlap;		break;
	case DOUBLE_SLAP:	attack = new DoubleSlap;	break;
	case BEAT_RUSH_R:	attack = new BeatRushR;		break;
	}
	attack->Initialize(&hand_l, &hand_r);
	RandomHandState();
}

void Boss::ActionEnd() {
	action_end_flag_ = true;
	hand_dmg_flag_   = false;
}

void Boss::WeakStateStart() {
	weak_state_start_flag_ = true;
}

void Boss::SwitchStateWait() {
	if (action_end_flag_) {
		delete attack;
		attack = new Wait;
		attack->Initialize(&hand_l, &hand_r);
		action_end_flag_ = false;
	}
}

void Boss::SwitchStateDamage() {
	if (!hand_dmg_flag_) {
		delete attack;
		attack = new Damage;
		attack->Initialize(&hand_l, &hand_r);
		hand_dmg_flag_ = true;
	}
}

void Boss::SwitchStateWeak() {
	if (weak_state_start_flag_) {
		delete attack;
		attack = new Weak;
		attack->Initialize(&hand_l, &hand_r);
		weak_state_start_flag_ = false;
	}
}

void Boss::PlaySlapSE() {
	slap_se_->Play();
}

void Boss::PlayBeatSE() {
	beat_se_->Play(); 
}

void Boss::PlayBeatEffect(SimpleMath::Vector3 effect_pos) {
	DX12Effect.Play(beat_effect_, effect_pos); 
}

void Boss::SetWeakState(bool select) {
	weak_state_ = select;
}