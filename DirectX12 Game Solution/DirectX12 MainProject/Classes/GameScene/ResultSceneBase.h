/**
* @file ResultSceneBase.h
* @brief �N���A�E�Q�[���I�[�o�[�V�[�����ʏ����N���X
* @author ���㏃��
*/

#pragma once

#include "Classes/GameScene/SceneBase.h"

/**
* @brief ResultSceneBase��`
*/
class ResultSceneBase : public SceneBase {
public:
	void Update(const float deltaTime);

	virtual void Render()const;
};