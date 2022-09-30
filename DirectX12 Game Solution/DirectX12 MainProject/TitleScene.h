/**
* @file TitleScene.h
* @brief タイトルシーン処理
* @author 吹上純平
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
	SceneBase scene_base_; /**< シーンベース */
	DX9::SPRITE black_; /** 黒画像格納 */
	int black_alpha_; /**< 黒画像のアルファ値 */
	bool start_flag_; /**< ゲームを始めるか */

	const int WIDTH_MAX_ = 1280; /**< 画像の横幅 */
	const int HIGHT_MAX_ = 720; /**< 画像の縦幅 */
	const int COLOR_MAX_ = 255; /**< 色の最大値 */
	const int BLACK_ALPHA_SPEED_ = 180; /**< 黒画像アルファ値増減速度 */
	const float TITLE_TEXT_POS_Y_ = 210.0f; /**< タイトルY座標 */
};