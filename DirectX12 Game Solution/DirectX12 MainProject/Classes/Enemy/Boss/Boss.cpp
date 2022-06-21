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

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_l.Initialize();
	hand_r.Initialize();
	std::random_device seed;
	random_engine_ = std::mt19937(seed());
	randomDist = std::uniform_int_distribution<>(1, 6);
	random_hand_dist_ = std::uniform_int_distribution<>(ROCK, PAPER);
	attack = new Wait;
	attack->Initialize(&hand_l, &hand_r);
	action_end_flag_ = false;
	hand_state_ = ROCK;
	old_hand_state_ = ROCK;
	slap_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Slap.wav");
	beat_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"SE/Beat.wav");
	hand_dmg_flag_ = false;
}

void Boss::LoadAseets() {
	body.LoadAssets();
	core.LoadAssets();
	hand_l.LoadAssets();
	hand_r.LoadAssets();
	beat_effect_ = DX12Effect.Create(L"Effect/Eff_shock/Eff_shock.efk");
}

void Boss::Update(const float deltaTime, ObjectManager* obj_m) {
	core.Update(deltaTime, obj_m->GetBossDmgFlag());
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
	attack->Update(deltaTime, obj_m, this);
	SwitchStateWait();
	if (obj_m->IsBossHandLDmg() ||
		obj_m->IsBossHandRDmg()) {
		SwitchStateDamage();
	}
}

void Boss::Render() {
	body.Render();
	core.Render();
	hand_l.Render();
	hand_r.Render();
}

void Boss::Render2D() {
	core.Render2D();
	hand_r.Render2D(1000.0f);
	hand_l.Render2D(0.0f);

}

void Boss::RandomAttackState() {	//É{ÉXÇÃHPÇ…î‰ó·ÇµÇƒçUåÇÇÃéÌóﬁïœâª
	int boss_hp_ = GetBossHP();
	bool normal_time_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_time_   = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;
	int max_random_num_;
	int old_state_ = attack_state_;

	if (normal_time_) {
		max_random_num_ = NORMAL_MODE_MAX_;
	}
	else if (hard_time_) {
		max_random_num_ = HARD_MODE_MAX_;
	}
	else {
		max_random_num_ = VERY_HARD_MODE_MAX_;
	}

	while (true) {
		attack_state_ = randomDist(random_engine_);
		if (attack_state_ <= max_random_num_ && attack_state_ != old_state_) {
			break;
		}
	}
	
	SwitchStateAttack();
}

void Boss::RandomHandState() {
	if (same_state_flag_) {	//2òAë±ìØÇ∂èÛë‘ÇæÇ¡ÇΩèÍçáÇ‡Ç§ï–ï˚ÇÃèÛë‘Ç…Ç∑ÇÈ
		hand_state_ = (old_hand_state_ == ROCK) ? PAPER : ROCK;
		same_state_flag_ = false;
	}
	else {
		hand_state_ = random_hand_dist_(random_engine_);
	}

	if (hand_state_ == old_hand_state_) {
		same_state_flag_ = true;
	}

	old_hand_state_ = hand_state_;
}

void Boss::SwitchStateAttack() {
	delete attack;
	switch (attack_state_) {
	case RIGHT_BEAT:	attack = new RightBeat;		break;
	case LEFT_BEAT:		attack = new LeftBeat;		break;
	case LEFT_SLAP:		attack = new LeftSlap;		break;
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

void Boss::PlaySlapSE() {
	slap_se_->Play();
}

void Boss::PlayBeatSE() {
	beat_se_->Play(); 
}

void Boss::PlayBeatEffect(SimpleMath::Vector3 effect_pos) {
	DX12Effect.Play(beat_effect_, effect_pos); 
}