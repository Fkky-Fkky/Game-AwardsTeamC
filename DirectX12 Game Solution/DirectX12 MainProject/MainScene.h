//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "Classes/My_Camera/My_Camera.h"
#include "Classes/PlayerTestCamera/PlayerTestCamera.h"
#include "Classes/Player/Player.h"
#include "Classes/Ground/Ground.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/Collision.h"
#include "Classes/Collision/ObjectManager.h"

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
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	My_Camera camera;
	PlayerTestCamera player_camera;
	Player player;
	Ground ground;
	Boss boss;
	Collision collision;
	ObjectManager object;
};