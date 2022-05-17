//
// BossTestScene.h
//

#pragma once

#include "Scene.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/PlayerTestCamera/PlayerTestCamera.h"
#include "Classes/Player/Player.h"
#include "Classes/Ground/Ground.h"
#include "Classes/My_Camera/My_Camera.h"
#include "Classes/Collision/Collision.h"
#include "Classes/Collision/ObjectManager.h"
#include "Classes/GameScene/SceneChange.h"
#include "Classes/UI/UI.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class BossTestScene final : public Scene {
public:
	BossTestScene();
	virtual ~BossTestScene() { Terminate(); }

	BossTestScene(BossTestScene&&) = default;
	BossTestScene& operator= (BossTestScene&&) = default;

	BossTestScene(BossTestScene const&) = delete;
	BossTestScene& operator= (BossTestScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

private:
	Boss boss_;
	PlayerTestCamera camera_;
	Player player_;
	Ground ground_;
	Collision collision_;
	ObjectManager object_;
	SceneChange scene_change_;
	UI ui;
};