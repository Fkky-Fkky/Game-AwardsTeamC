/**
* @file InputManager.h
* @brief �L�[�{�[�h�E�R���g���[���[���͊Ǘ��N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/*
* @brief InputManager�N���X��`
*/
class InputManager {
public:

	static InputManager& GetInstance() {
		static InputManager self_;
		return self_;
	}

	/**
	* @brief ���ړ����͂�����Ă��邩
	*
	* @retval TRUE ���͂���Ă���
	* @retval FALSE ���͂���Ă��Ȃ�
	*/
	bool IsInputLeftMove() { return DXTK->KeyState->A || DXTK->GamePadState->thumbSticks.leftX < 0; }

	/**
	* @brief �E�ړ����͂�����Ă��邩
	*
	* @retval TRUE ���͂���Ă���
	* @retval FALSE ���͂���Ă��Ȃ�
	*/
	bool IsInputRightMove() { return DXTK->KeyState->D || DXTK->GamePadState->thumbSticks.leftX > 0; }

	/**
	* @brief �W�����v���͂�����Ă��邩
	*
	* @retval TRUE ���͂���Ă���
	* @retval FALSE ���͂���Ă��Ȃ�
	*/
	bool IsInputJump() { return DXTK->KeyEvent->pressed.W || DXTK->GamePadEvent->a == GamePad::ButtonStateTracker::PRESSED; }

	/**
	* @brief �U�����͂�����Ă��邩
	*
	* @retval TRUE ���͂���Ă���
	* @retval FALSE ���͂���Ă��Ȃ�
	*/
	bool IsInputAttack() { return DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->x == GamePad::ButtonStateTracker::PRESSED; }

	/**
	* @brief ������͂�����Ă��邩
	*
	* @retval TRUE ���͂���Ă���
	* @retval FALSE ���͂���Ă��Ȃ�
	*/
	bool IsInputDecision() { return DXTK->KeyEvent->pressed.Enter || DXTK->GamePadEvent->b == GamePad::ButtonStateTracker::PRESSED; }

private:
	InputManager() {};
};