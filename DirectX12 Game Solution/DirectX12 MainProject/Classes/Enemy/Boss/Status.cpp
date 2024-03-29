#include "Classes/Enemy/Boss/Status.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 値の初期化
*/
void boss::Status::Initialize() {
	damage_type_ = HAND;
	weak_count_ = 0;
	hp_ = BOSS_HP_MAX_;
	invincible_time_ = 0.0f;
	weak_time_ = 0.0f;
	is_set_weak_time_ = false;
	hand_dmg_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/SE/BossHandDmg.wav");
	body_dmg_se_ = XAudio::CreateSoundEffect(DXTK->AudioEngine, L"BGM_SE/SE/BossBodyDmg.wav");
}

/**
* @brief Statusの更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
*/
void boss::Status::Update(const float deltaTime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltaTime, 0.0f);
	if (IsWeak()) {
		weak_time_ = std::max(weak_time_ - deltaTime, 0.0f);
		if (weak_time_ <= 0.0f) {
			weak_count_ = 0;
			is_set_weak_time_ = false;
		}
	}

	bool is_invincible_ = invincible_time_ > 0.0f; /**< 無敵状態か */
	if (obj_m->IsBossHandDmg()) {
		if (!is_invincible_) {
			damage_type_ = HAND;
			DamageProcess();
			hand_dmg_se_->Play();
			weak_count_++;
		}
	}
	if (obj_m->IsBossBodyDmg()) {
		if (!is_invincible_) {
			damage_type_ = BODY;
			DamageProcess();
			body_dmg_se_->Play();
		}
	}
	if (IsWeak() && !is_set_weak_time_) {
		weak_time_ = WEAK_TIME_MAX_;
		is_set_weak_time_ = true;
	}
}

/**
* @brief ダメージを受けた時の処理
* 
* ダメージを受けた部位によってダメージ量を変更する
*/
void boss::Status::DamageProcess() {
	float damage_num_ = 0.0f; /**< ダメージ量を格納 */
	switch (damage_type_) {
	case HAND:	damage_num_ = HAND_DAMAGE_;	break;
	case BODY:	damage_num_ = BODY_DAMAGE_;	break;
	default:	break;
	}
	hp_ -= damage_num_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}