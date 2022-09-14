#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

namespace player {
	class PlayerColision {
	public:
		PlayerColision() {};
		~PlayerColision() {};

		void LoadAssets(DX9::SkinnedModel* const model);
		void Update(const float deltaTime, const DX9::SkinnedModel* const model);
		void Render()const;
		BoundingOrientedBox GetColision() const { return collision_; }

	private:
		BoundingOrientedBox collision_;
		DX9::MODEL          collision_model_;

		const float COLLISION_SIZE_MULTIPLY_X_ = 0.5f;
		const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f;
		const float COLLISION_SIZE_MULTIPLY_Z_ = 0.5f;
		const float CENTER_PLUS_Y_VALUE_ = 2.0f;
	};
}