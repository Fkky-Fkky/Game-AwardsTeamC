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
	const float RANGE_ = 100.0f; /**< 照らす範囲 */
};