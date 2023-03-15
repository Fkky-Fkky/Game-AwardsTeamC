/**
* @file MainScene.h
* @brief メインシーン処理
* @author 吹上純平
*/

#pragma once

#include "Scene/Scene.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Player/Player.h"
#include "Classes/Ground/Ground.h"
#include "Classes/My_Camera/My_Camera.h"
#include "Classes/Collision/Collision.h"
#include "Classes/Object/ObjectManager.h"
#include "Classes/GameScene/SceneChange.h"
#include "Classes/GameScene/SceneBase.h"
#include "Classes/UI/UI.h"
#include "Classes/My_Light/My_Light.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	Boss boss_; /**< ボスクラス */
	My_Camera camera_; /**< カメラクラス */
	Player player_; /**< プレイヤークラス */
	Ground ground_; /**< グラウンドクラス */
	Collision collision_; /**< コリジョンクラス */
	ObjectManager object_; /**< オブジェクトクラス */
	SceneBase scene_base_; /**< シーンベースクラス */
	SceneChange scene_change_; /**< シーン切り替えクラス */
	UI ui; /**< UIクラス */
	My_Light light_; /**< ライトクラス */
};