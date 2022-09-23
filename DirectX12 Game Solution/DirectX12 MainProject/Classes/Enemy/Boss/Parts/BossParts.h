/**
* @file BossParts.h
* @brief 各ボスパーツ基底クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @brief BossPartsクラス定義
*/
class BossParts {
public:
	virtual void Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote);
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render()const;

protected:
	SimpleMath::Vector3 position_; /**< 座標を格納 */
	SimpleMath::Vector3 rotation_; /**< 回転を格納 */
	DX9::SKINNEDMODEL model_; /**< モデルを格納 */
};