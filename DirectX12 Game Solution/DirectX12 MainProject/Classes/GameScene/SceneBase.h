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

private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;
};