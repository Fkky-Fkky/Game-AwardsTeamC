#pragma once

#include "Classes/Enemy/Boss/Parts/BossParts.h"

class BossBody : public BossParts {
public:
	virtual void Initialize();
	void LoadAssets();
	void Render();
private:
	DX9::MODEL boss_body_;
	BoundingBox cube_coll_;
	DX9::MODEL cube_;
	const float BODY_INIT_POS_Y_ = 5.0f;
	const float BODY_INIT_POS_Z_ = 15.0f;
	const float BODY_SCALE_ = 0.3f;
};