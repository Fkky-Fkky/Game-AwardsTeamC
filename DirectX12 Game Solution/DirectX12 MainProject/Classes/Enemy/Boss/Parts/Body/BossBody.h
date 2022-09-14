#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"

class ObjectManager;
class Boss;

namespace boss {
	class BossBody : public BossParts {
	public:
		virtual void Initialize();
		void LoadAssets();
		void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);
		void Render()const;
		BoundingOrientedBox GetBodyCollision() const { return body_coll_; }
	private:
		void WeakAction();

		BoundingOrientedBox body_coll_;
		DX9::MODEL coll_model_;
		float time_delta_;
		float shake_time_;
		float entyoku_time_;
		bool is_weak_;
		bool is_shake_;
		bool shake_set_flag_;

		const float BODY_INIT_POS_Y_ = 17.0f;
		const float BODY_INIT_POS_Z_ = 15.0f;
		const float BODY_INIT_ROT_X_ = -20.0f;
		const float BODY_WEAK_POS_Y_ = 5.0f;
		const float BODY_WEAK_POS_Z_ = 5.0f;
		const float BODY_SCALE_ = 0.8f;
		const float COLLISION_SIZE_X_ = 0.1f;
		const float COLLISION_SIZE_Z_ = 0.8f;
	};
}