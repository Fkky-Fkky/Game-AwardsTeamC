#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"

class ObjectManager;
class Boss;

namespace boss {
	class BossBody : public BossParts {
	public:
		BossBody() {
			time_delta_	  = 0.0f;
			shake_time_   = 0.0f;
			body_jump_y_  = 0.0f;
			body_jump_time_ = 0.0f;
			is_weak_		= false;
			is_shake_		= false;
			shake_set_flag_ = false;
			is_body_death_ = false;
		}
		~BossBody() {};

		virtual void Initialize();
		void LoadAssets();
		void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);
		void Render()const;

		bool IsBodyDeath() const { return is_body_death_; }
		BoundingOrientedBox GetBodyCollision() const { return body_coll_; }
	private:
		void WeakAction();
		void DeathAction();

		BoundingOrientedBox body_coll_;
		DX9::MODEL coll_model_;
		float time_delta_;
		float shake_time_;
		float body_jump_y_;
		float body_jump_time_;
		bool is_weak_;
		bool is_shake_;
		bool shake_set_flag_;
		bool is_body_death_;

		const float BODY_INIT_POS_Y_ = 17.0f;
		const float BODY_INIT_POS_Z_ = 15.0f;
		const float BODY_INIT_ROT_X_ = -20.0f;
		const float BODY_WEAK_POS_Y_ = 5.0f;
		const float BODY_WEAK_POS_Z_ = 5.0f;
		const float BODY_SCALE_ = 0.8f;
		const float COLLISION_SIZE_X_ = 0.1f;
		const float COLLISION_SIZE_Z_ = 0.8f;
		const float BODY_UP_SPEED_Y_ = 10.0f;
		const float MOVE_SPEED_Z_ = 20.0f;
		const float ROTATION_SPEED_ = 10.0f;
		const float SHAKE_TIME_MAX_ = 0.2f;
		const float ROTAION_SPEED_ = 200.0f;
		const float DEATH_ROTATION_X_ = 40.0f;

		const float JUMP_SPEED_ = 1.0f;
		const float HALF_		= 0.5f;
		const float GRAVITY_	= 2.0f;
	};
}