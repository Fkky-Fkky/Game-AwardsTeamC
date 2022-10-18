/**
* @file ResultSceneBase.h
* @brief クリア・ゲームオーバーシーン共通処理クラス
* @author 吹上純平
*/

#pragma once

#include "Classes/GameScene/SceneBase.h"

/**
* @brief ResultSceneBase定義
*/
class ResultSceneBase : public SceneBase {
public:
	void Update(const float deltaTime);

	virtual void Render()const;
};