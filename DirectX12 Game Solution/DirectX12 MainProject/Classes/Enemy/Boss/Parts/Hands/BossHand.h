#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

using namespace DirectX;

class BossHand : public BossParts{
public:
	BossHand() {
		hand_hp_ = 0;
		bezier_t = 0.0f;
		attack_flag_ = false;
	}

	~BossHand() {};
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render();
	void Render2D(float pos_x);

	int GetHandHp() { return hand_hp_; }
	bool GetAttackFlag() { return attack_flag_; }
	BoundingOrientedBox GetHandCollision() { return collision; }
	SimpleMath::Vector3 GetHandPos() { return position; }
	SimpleMath::Vector3 GetRotation() { return rotation; }
	void SetHandPos(SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(bool attack_flag) { attack_flag_ = attack_flag; }
	void HandDamageProcess();

private:

	void SusiZanmai();

	float bezier_t;

	bool attack_flag_;

protected:

	BoundingOrientedBox collision;
	DX9::MODEL collision_model;
	DX9::SPRITEFONT font_;
	int hand_hp_;

	const float INITIAL_POS_Y = 10.0f;
	const float INITIAL_POS_Z = 3.0f;
};