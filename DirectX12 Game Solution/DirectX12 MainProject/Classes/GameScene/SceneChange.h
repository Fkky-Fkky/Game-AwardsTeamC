/**
* @file SceneChamge.h
* @brief シーン切り替え処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

/**
* @brief SceneChangeクラス定義
*/
class SceneChange {
public:
	SceneChange() {
		black_alpha_ = 0.0f;
		white_alpha_ = 0.0f;
		wait_time_	 = 0.0f;
		scene_change_flag_ = false;
		is_game_start_ = false;
		is_game_clear_ = false;
	};

	~SceneChange() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, const ObjectManager* obj_m);
	void Render2D()const;

	/**
	* @brief シーンを切り替えるか
	* 
	* @retval TRUE 切り替える
	* @retval FALSE 切り替えない
	*/
	bool IsSceneChange() const { return scene_change_flag_; }

	/**
	* @brief ゲームをクリアしたか
	* 
	* @retval TRUE クリア
	* @retval FALSE ゲームオーバー
	*/
	bool IsGameClear() const { return is_game_clear_; }

	/**
	* @brief ゲームを開始するか
	* 
	* @retval TRUE する
	* @retval FALSE しない
	*/
	bool IsGameStart() const { return is_game_start_; }
private:
	DX9::SPRITE black_; /**< 黒画像格納 */
	DX9::SPRITE white_; /**< 白画像格納 */

	float black_alpha_; /**< 黒画像のアルファ値 */
	float white_alpha_; /**< 白画像のアルファ値 */
	float wait_time_; /**< 待機時間 */
	bool scene_change_flag_; /**< シーン切り替えフラグ */
	bool is_game_start_; /**< ゲームを開始するか */
	bool is_game_clear_; /**< ゲームをクリアしたか */

	const int WIDTH_MAX_ = 1280; /**< 横幅最大値 */
	const int HIGHT_MAX_ = 720; /**< 縦幅最大値 */
	const float ALPHA_SPEED_  = 180.0f; /**< アルファ値増減速度 */
	const float COLOR_MAX_	  = 255.0f; /**< 色の最大値 */
	const float SPRITE_POS_Z_ = -10.0f; /**< 画像のZ座標 */
	const float PLAYER_DEAD_WAIT_TIME_MAX_ = 1.5f; /**< プレイヤー死亡時の待機時間 */
	const float BOSS_DEAD_WAIT_TIME_MAX_   = 1.0f; /**< ボス死亡時の待機時間 */
};