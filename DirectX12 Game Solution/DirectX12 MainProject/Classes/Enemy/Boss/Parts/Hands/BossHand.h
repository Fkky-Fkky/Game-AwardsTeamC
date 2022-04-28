#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/BossParts.h"

using namespace DirectX;

class BossHand : public BossParts{
public:
	BossHand();
	~BossHand() {};
	virtual void Initialize(SimpleMath::Vector3 pos, SimpleMath::Vector3 rote);
	virtual void LoadAssets(LPCWSTR file_name);
	virtual void Update(const float deltaTime);
	virtual void Render();

	bool GetAttackFlag() { return attack_flag; }
	BoundingOrientedBox GetHandCollision() { return collision; }
	SimpleMath::Vector3 GetHandPos() { return position; }
	SimpleMath::Vector3 GetRotation() { return rotation; }
	void SetHandPos(SimpleMath::Vector3 position_) { position = position_; }
	void SetHandRote(SimpleMath::Vector3 rotation_) { rotation = rotation_; }
	void SetAttackFlag(bool attack_flag_) { attack_flag = attack_flag_; }


private:

	void SusiZanmai();

	float bezier_t;

	bool attack_flag;

protected:

	BoundingOrientedBox collision;
	DX9::MODEL collision_model;

	const float INITIAL_POS_Y = 10.0f;
	const float INITIAL_POS_Z = 3.0f;

};