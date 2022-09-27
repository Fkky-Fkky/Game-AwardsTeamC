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
	const float DIRECTION_X_ = -20.0f; /**< �Ƃ炷X���� */
	const float DIRECTION_Y_ = -170.0f; /**< �Ƃ炷Y���� */
	const float DIRECTION_Z_ = 80.0f; /**< �Ƃ炷Z���� */
	const float LIGHT_POS_X_ = 0.0f; /**< ���C�g��X���W */
	const float LIGHT_POS_Y_ = 4.0f; /**< ���C�g��Y���W */
	const float LIGHT_POS_Z_ = -24.0f; /**< ���C�g��Z���W */
	const float RANGE_ = 100.0f; /**< �Ƃ炷�͈� */
};