/**
* @file TitleScene.h
* @brief �^�C�g���V�[������
* @author ���㏃��
*/

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
	SceneBase scene_base_; /**< �V�[���x�[�X */
	DX9::SPRITE black_; /** ���摜�i�[ */
	DX9::SPRITE title_text_; /**< �^�C�g���摜�i�[ */
	int text_alpha_; /**< �^�C�g���̃A���t�@�l�@*/
	int black_alpha_; /**< ���摜�̃A���t�@�l */
	bool start_flag_; /**< �Q�[�����n�߂邩 */

	const int WIDTH_MAX_ = 1280; /**< �摜�̉��� */
	const int HIGHT_MAX_ = 720; /**< �摜�̏c�� */
	const int COLOR_MAX_ = 255.0f; /**< �F�̍ő�l */
	const int BLACK_ALPHA_SPEED_ = 180; /**< ���摜�A���t�@�l�������x */
	const int TEXT_ALPHA_SPEED_ = 300; /**< �^�C�g���A���t�@�l�������x */
	const float TITLE_TEXT_POS_X_ = 640.0f; /**< �^�C�g��X���W */
	const float TITLE_TEXT_POS_Y_ = 360.0f; /**< �^�C�g��Y���W */
	const float TITLE_TEXT_ORIGIN_X_ = 600.0f; /**< �^�C�g���̌��_X */
	const float TITLE_TEXT_ORIGIN_Y_ = 150.0f; /**< �^�C�g���̌��_Y */
	const int TITLE_TEXT_WIDTH_ = 1200; /**< �^�C�g���摜�̕� */
	const int TITLE_TEXT_HIGHT_ = 300; /**< �^�C�g���摜�̍��� */
};