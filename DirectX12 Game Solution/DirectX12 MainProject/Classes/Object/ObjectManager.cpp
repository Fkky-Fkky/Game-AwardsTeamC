#include "Classes/Object/ObjectManager.h"
#include "Classes/Player/Player.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/Collision.h"

/**
* @brief �v���C���[�̐ݒ�
* 
* @param[out] player �v���C���[�N���X
*/
void ObjectManager::SetPlayer(Player* const player) {
	player_ = player;
}

/**
* @brief �{�X�̐ݒ�
* 
* @param[out] boss �{�X�N���X
*/
void ObjectManager::SetBoss(Boss* const boss) {
	boss_ = boss;
}

/**
* @brief �R���W�����̐ݒ�
* 
* @param[out] collision �R���W�����N���X
*/
void ObjectManager::SetCollision(Collision* const collision) {
	collision_ = collision;
}

/**
* @brief �v���C���[�̃R���W�����擾
* 
* @return �v���C���[�̃R���W����
*/
BoundingOrientedBox ObjectManager::GetPlayerCollision() const {
	return player_->GetPlayerCollision();
}

/**
* @brief �v���C���[�̍U���R���W�����擾
* 
* @return �v���C���[�̍U���R���W���� 
*/
BoundingOrientedBox ObjectManager::GetPlayerAttackCollision() const {
	return player_->GetPlayerAttackCollision();
}

/**
* @brief �{�X�̃R���W�����擾
* 
* @return �{�X�̃R���W����
*/
BoundingOrientedBox ObjectManager::GetBossBodyCollision() const {
	return boss_->GetBodyCollision();
}

/**
* @brief �{�X�̉E��R���W�����擾
* 
* @return �{�X�E��R���W����
*/
BoundingOrientedBox ObjectManager::GetBossRHandCollision() const {
	return boss_->GetRHandCollision();
}

/**
* @brief �{�X�̍���R���W�����擾
* 
* @return �{�X����R���W����
*/
BoundingOrientedBox ObjectManager::GetBossLHandCollision() const {
	return boss_->GetLHandCollision();
}

/**
* @�{�X��HP�擾
* 
* @return �{�X��HP
*/
float ObjectManager::GetBossHP() const {
	return boss_->GetBossHP();
}

/**
* @brief �v���C���[��HP�擾
* 
* @return �v���C���[��HP
*/
float ObjectManager::GetPlayerHP() const {
	return player_->GetPlayerHP();
}

/**
* @brief �v���C���[���U�����Ă��邩
* 
* @retval TRUE �U�����Ă���
* @retval FALSE �U�����Ă��Ȃ�
*/
bool ObjectManager::IsPlayerAttack() const {
	return player_->IsPlayerAttack();
}

/**
* @brief �v���C���[���_���[�W���󂯂Ă��邩
* 
* @retval TRUE �󂯂�
* @retval FALSE �󂯂Ă��Ȃ�
*/
bool ObjectManager::IsPlayerDmg() const {
	return collision_->GetPlayerDmgFlagR() || collision_->GetPlayerDmgFlagL();
}

/**
* @brief �v���C���[������ł��邩
* 
* @retval TRUE ����ł���
* @retval FALSE ����ł��Ȃ�
*/
bool ObjectManager::IsPlayerDeath() const {
	return player_->IsPlayerDeath();
}

/**
* @brief �{�X�E�肪�U�����Ă��邩
* 
* @retval TRUE �U�����Ă���
* @retval FALSE �U�����Ă��Ȃ�
*/
bool ObjectManager::IsBossRAttack() const {
	return boss_->IsRHandAttack();
}

/**
* @brief �{�X���肪�U�����Ă��邩
* 
* @retval TRUE �U�����Ă���
* @retval FALSE �U�����Ă��Ȃ�
*/
bool ObjectManager::IsBossLAttack() const {
	return boss_->IsLHandAttack();
}

/**
* @brief �{�X�{�̂��_���[�W���󂯂Ă��邩
* 
* @retval TRUE �󂯂�
* @retval FALSE �󂯂Ă��Ȃ�
*/
bool ObjectManager::IsBossBodyDmg() const {
	return collision_->IsBossBodyDmg();
}

/**
* @brief �{�X�̎肪�J���Ă��邩
* 
* @retval TRUE �J���Ă���
* @retval FALSE �����Ă���
*/
bool ObjectManager::IsBossHandOpen() const {
	return boss_->IsHandOpen();
}

/**
* @brief �肪�_���[�W���󂯂Ă��邩
* 
* @retval TRUE �󂯂Ă���
* @retval FALSE �󂯂Ă��Ȃ�
*/
bool ObjectManager::IsBossHandDmg() const {
	return collision_->IsBossHandDmg();
}

/**
* @brief �{�X���E�B�[�N��Ԃ�
* 
* @retval TRUE �E�B�[�N���
* @retval FALSE �E�B�[�N�ł͂Ȃ�
*/
bool ObjectManager::IsBossWeak() const {
	return boss_->IsBossWeak();
}

/**
* @brief �{�X������ł��邩
* 
* @retval TRUE ����ł���
* @retval FALSE ����ł��Ȃ�
*/
bool ObjectManager::IsBossDeath() const {
	return boss_->IsBossDeath();
}

/**
* @brief �J�����c�h�ꂷ�邩
* 
* @retval TRUE �h�炷
* @retval FALSE �h�炳�Ȃ�
*/
bool ObjectManager::IsCameraVerticalShake() const {
	return boss_->IsVerticalShake();
}

/**
* @brief �J�������h�ꂳ���邩
* 
* @retval TRUE �h�炷
* @retval FALSE �h�炳�Ȃ�
*/
bool ObjectManager::IsCameraSideShake() const {
	return boss_->IsSideShake();
}

/**
* @brief �v���C���[�̍��W�擾
* 
* @return �v���C���[�̍��W
*/
SimpleMath::Vector3 ObjectManager::GetPlayerPos() const {
	return player_->GetPlayerPosition();
}