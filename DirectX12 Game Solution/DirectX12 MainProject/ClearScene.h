//
// ClearScene.h
//

#pragma once

#include "Scene.h"

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
    DX12::DESCRIPTORHEAP descriptorHeap;
    DX12::SPRITEBATCH    spriteBatch;
    DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

private:
	DX9::SPRITE clear_;
};