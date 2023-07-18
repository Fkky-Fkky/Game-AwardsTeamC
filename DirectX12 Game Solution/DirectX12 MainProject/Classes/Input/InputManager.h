/**
* @file InputManager.h
* @brief キーボード・コントローラー入力管理クラス
* @author 吹上純平
*/

#pragma once

/**
* インクルードファイル
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/*
* @brief InputManagerクラス定義
*/
class InputManager {
public:

	static InputManager& GetInstance() {
		static InputManager self_;
		return self_;
	}

	/**
	* @brief 左移動入力がされているか
	*
	* @retval TRUE 入力されている
	* @retval FALSE 入力されていない
	*/
	bool IsInputLeftMove() { return DXTK->KeyState->A || DXTK->GamePadState->thumbSticks.leftX < 0; }

	/**
	* @brief 右移動入力がされているか
	*
	* @retval TRUE 入力されている
	* @retval FALSE 入力されていない
	*/
	bool IsInputRightMove() { return DXTK->KeyState->D || DXTK->GamePadState->thumbSticks.leftX > 0; }

	/**
	* @brief ジャンプ入力がされているか
	*
	* @retval TRUE 入力されている
	* @retval FALSE 入力されていない
	*/
	bool IsInputJump() { return DXTK->KeyEvent->pressed.W || DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED; }

	/**
	* @brief 攻撃入力がされているか
	*
	* @retval TRUE 入力されている
	* @retval FALSE 入力されていない
	*/
	bool IsInputAttack() { return DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED; }

	/**
	* @brief 決定入力がされているか
	*
	* @retval TRUE 入力されている
	* @retval FALSE 入力されていない
	*/
	bool IsInputDecision() { return DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED; }

private:
	InputManager() {};
};