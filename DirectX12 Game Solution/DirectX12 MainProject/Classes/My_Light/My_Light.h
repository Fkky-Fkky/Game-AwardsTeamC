/**
* @file My_Light.h
* @brief ���C�g�����N���X
* @author ���㏃��
*/

#pragma once

/**
* �C���N���[�h�t�@�C��
*/
#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

/**
* @brief My_Light�N���X��`
*/
class My_Light {
public:
	My_Light() {};
	~My_Light(){};
	void LoadAssets();
private:
	const float RANGE_ = 100.0f; /**< �Ƃ炷�͈� */
};