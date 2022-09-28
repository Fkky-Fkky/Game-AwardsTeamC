/**
* @file PlayerCollision.h
* @brief プレイヤーのコリジョン処理クラス
* @outhor 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

namespace player {
	/**
	* @brief PlayerCollsionクラス定義
	*/
	class PlayerCollision {
	public:
		PlayerCollision() {};
		~PlayerCollision() {};

		void LoadAssets(DX9::SkinnedModel* const model);
		void Update(const DX9::SkinnedModel* const model);

		/**
		* @brief プレイヤーコリジョンの取得
		* 
		* @return コリジョン
		*/
		BoundingOrientedBox GetColision() const { return collision_; }

	private:
		BoundingOrientedBox collision_; /**< プレイヤーのコリジョン格納 */

		const float COLLISION_SIZE_MULTIPLY_X_ = 0.5f; /**< コリジョンXサイズ */
		const float COLLISION_SIZE_MULTIPLY_Y_ = 2.5f; /**< コリジョンYサイズ */
		const float COLLISION_SIZE_MULTIPLY_Z_ = 0.5f; /**< コリジョンZサイズ */
		const float CENTER_PLUS_Y_VALUE_ = 2.0f; /**< コリジョンのY座標 */
	};
}