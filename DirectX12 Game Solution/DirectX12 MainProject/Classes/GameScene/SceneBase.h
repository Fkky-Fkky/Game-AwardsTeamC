#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class SceneBase {
public:
	SceneBase() {
		dx9GpuDescriptor = {};
	}

	void LoadAssets();
	void Render()const;

	void SetBGM(LPCWSTR bgm_file);
	void PlayBGM()const;
private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	DX9::MEDIARENDERER bgm_;
};