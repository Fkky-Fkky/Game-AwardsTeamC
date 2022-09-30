/**
* @file GameOverScene.h
* @brief �Q�[���I�[�o�[�V�[������
* @author ���㏃��
*/

#pragma once

#include "Scene.h"
#include "Classes/GameScene/SceneBase.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class GameOverScene final : public Scene {
public:
	GameOverScene();
	virtual ~GameOverScene() { Terminate(); }

	GameOverScene(GameOverScene&&) = default;
	GameOverScene& operator= (GameOverScene&&) = default;

	GameOverScene(GameOverScene const&) = delete;
	GameOverScene& operator= (GameOverScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	SceneBase scene_base_; /**< �V�[���x�[�X */
	const float TEXT_INIT_POS_Y_ = 180.0f; /**< �e�L�X�g�̏���Y���W */
};