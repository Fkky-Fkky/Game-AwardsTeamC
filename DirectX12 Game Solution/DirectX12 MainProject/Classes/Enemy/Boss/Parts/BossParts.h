/**
* @file BossParts.h
* @brief �e�{�X�p�[�c���N���X
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
* @brief BossParts�N���X��`
*/
class BossParts {
public:
	virtual void Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote);
	virtual void LoadAssets(const LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render()const;

protected:
	SimpleMath::Vector3 position_; /**< ���W���i�[ */
	SimpleMath::Vector3 rotation_; /**< ��]���i�[ */
	DX9::SKINNEDMODEL model_; /**< ���f�����i�[ */
};