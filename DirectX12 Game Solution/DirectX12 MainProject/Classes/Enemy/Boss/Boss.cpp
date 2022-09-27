#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief �l�̏�����
*/
void Boss::Initialize() {
	status_.Initialize();
	body_.Initialize();
	action_.Initialize();
}

/**
* @brief �e���f���̓ǂݍ���
*/
void Boss::LoadAseets() {
	body_.LoadAssets();
	action_.LoadAssets();
}

/**
* @brief �e�p�[�c�̍X�V
* 
* @param[in] deltaTime ����
* @param[in] obj_m �I�u�W�F�N�g�}�l�[�W���[
*/
void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	body_.Update(deltaTime, obj_m, this);
	status_.Update(deltaTime, obj_m);
	action_.Update(deltaTime, obj_m);
}

/**
* @brief �e�p�[�c�`��
*/
void Boss::Render() const {
	body_.Render();
	action_.Render();
}