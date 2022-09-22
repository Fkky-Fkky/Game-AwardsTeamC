//
// TitleScene.h
//

#pragma once

#include "Scene.h"
#include "Classes/GameScene/SceneBase.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class TitleScene final : public Scene {
public:
	TitleScene();
	virtual ~TitleScene() { Terminate(); }

	TitleScene(TitleScene&&) = default;
	TitleScene& operator= (TitleScene&&) = default;

	TitleScene(TitleScene const&) = delete;
	TitleScene& operator= (TitleScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;


private:
	SceneBase scene_base_;
	DX9::SPRITE title_;
	DX9::SPRITE black_;
	float black_alpha_;
	bool start_flag_;

	const int WIDTH_MAX_ = 1280;
	const int HIGHT_MAX_ = 720;
	const float ALPHA_SPEED_ = 180.0f;
	const float ALPHA_MAX_ = 255.0f;
};