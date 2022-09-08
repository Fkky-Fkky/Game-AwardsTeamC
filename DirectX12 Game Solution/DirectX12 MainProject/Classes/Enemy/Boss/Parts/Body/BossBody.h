#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"

class ObjectManager;

class BossBody : public BossParts {
public:
	virtual void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* const obj_m_);
	void Render()const;
	BoundingOrientedBox GetBodyCollision() const { return body_coll_; }
private:
	BoundingOrientedBox body_coll_;
	DX9::MODEL coll_model_;
	const float BODY_INIT_POS_Y_ = 17.0f;
	const float BODY_INIT_POS_Z_ = 15.0f;
	const float BODY_INIT_ROT_X_ = -10.0f;
	const float BODY_DOWN_POS_Y_ = 5.0f;
	const float BODY_SCALE_ = 0.8f;
	const float COLLISION_SIZE_X_ = 1.5f;
	const float COLLISION_SIZE_Z_ = 1.5f;
};