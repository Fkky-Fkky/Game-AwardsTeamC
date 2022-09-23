#include "Classes/Enemy/Boss/Parts/BossParts.h"

/**
* @brief �l�̏�����
* 
* ���z�֐�
* @param[in] pos ���W
* @param[in] rote ��]
*/
void BossParts::Initialize(const SimpleMath::Vector3 pos, const SimpleMath::Vector3 rote) {
	position_ = pos;
	rotation_ = rote;
}

/**
* @brief ���f���ǂݍ���
* 
* ���z�֐�
* @param[in] file_name �ǂݍ��ރt�@�C����
*/
void BossParts::LoadAssets(const LPCWSTR file_name) {
	model_ = DX9::SkinnedModel::CreateFromFile(DXTK->Device9, file_name);
}

/**
* @brief ���f���̃��[�V�����Đ�
* 
* ���z�֐�
* @param[in] deltaTime ����
*/
void BossParts::Update(const float deltaTime) {
	model_->AdvanceTime(deltaTime);
}

/**
* @brief ���f���`��
* 
* ���z�֐�
*/
void BossParts::Render() const {
	model_->SetPosition(position_);
	model_->SetRotation(
		XMConvertToRadians(rotation_.x),
		XMConvertToRadians(rotation_.y),
		XMConvertToRadians(rotation_.z)
	);
	model_->Draw();
}