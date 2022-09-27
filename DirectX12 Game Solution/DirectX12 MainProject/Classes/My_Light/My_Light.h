/**
* @file My_Light.h
* @brief ライト処理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @brief My_Lightクラス定義
*/
class My_Light {
public:
	My_Light() {};
	~My_Light(){};
	void LoadAssets();
private:
	const float DIRECTION_X_ = -20.0f; /**< 照らすX方向 */
	const float DIRECTION_Y_ = -170.0f; /**< 照らすY方向 */
	const float DIRECTION_Z_ = 80.0f; /**< 照らすZ方向 */
	const float LIGHT_POS_X_ = 0.0f; /**< ライトのX座標 */
	const float LIGHT_POS_Y_ = 4.0f; /**< ライトのY座標 */
	const float LIGHT_POS_Z_ = -24.0f; /**< ライトのZ座標 */
	const float RANGE_ = 100.0f; /**< 照らす範囲 */
};