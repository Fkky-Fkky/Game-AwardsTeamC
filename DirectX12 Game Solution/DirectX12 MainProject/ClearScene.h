/**
* @file ClearScene.h
* @brief クリアシーン処理
* @author 吹上純平
*/

#pragma once

#include "Scene.h"
#include "Classes/GameScene/SceneBase.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class ClearScene final : public Scene {
public:
	ClearScene();
	virtual ~ClearScene() { Terminate(); }

	ClearScene(ClearScene&&) = default;
	ClearScene& operator= (ClearScene&&) = default;

	ClearScene(ClearScene const&) = delete;
	ClearScene& operator= (ClearScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	SceneBase scene_base_; /**< シーンベース */
	const float TEXT_INIT_POS_Y_ = 240.0f; /**< テキストの初期Y座標 */
};