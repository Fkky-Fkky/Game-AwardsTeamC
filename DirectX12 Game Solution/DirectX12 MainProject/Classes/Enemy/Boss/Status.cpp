#include "Classes/Enemy/Boss/Status.h"
#include "Classes/Collision/ObjectManager.h"

void Status::Initialize() {
	damage_type_ = HAND;
	weak_count_ = 0;
	hp_ = BOSS_HP_MAX_;
	invincible_time_ = 0.0f;
	weak_time_ = 0.0f;
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Status::Update(const float deltaTime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltaTime, 0.0f);
	if (IsWeak()) {
		weak_time_ = std::max(weak_time_ - deltaTime, 0.0f);
		if (weak_time_ <= 0.0f) {
			weak_count_ = 0;
		}
	}

	bool is_invincible_ = invincible_time_ > 0.0f;
	if (obj_m->IsBossHandLDmg() || obj_m->IsBossHandRDmg()) {
		if (!is_invincible_) {
			damage_type_ = HAND;
			DamageProcess();
			weak_count_++;
			if (IsWeak()) {
				weak_time_ = WEAK_TIME_MAX_;
			}
		}
	}
	if (obj_m->IsBossBodyDmg()) {
		if (!is_invincible_) {
			damage_type_ = BODY;
			DamageProcess();
		}
	}
}

void Status::DamageProcess() {
	float damage_num_ = 0.0f;
	switch (damage_type_) {
	case HAND:	damage_num_ = HAND_DAMAGE_;	break;
	case BODY:	damage_num_ = BODY_DAMAGE_;	break;
	default:	break;
	}
	hp_ -= damage_num_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}

void Status::Render2D() const {
	DX9::SpriteBatch->DrawString(
		font.Get(),
		SimpleMath::Vector2(1000.0f, 0.0f),
		DX9::Colors::White,
		L"%i",weak_count_
	);
}