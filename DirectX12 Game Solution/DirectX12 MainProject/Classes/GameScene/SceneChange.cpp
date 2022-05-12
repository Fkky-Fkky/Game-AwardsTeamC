#include "Classes/GameScene/SceneChange.h"
#include "Classes/Collision/ObjectManager.h"

void SceneChange::Update(ObjectManager* obj_m) {
	if (obj_m->GetPlayerHP() <= 0.0f ||
		obj_m->GetBossHP()	 <= 0) {
		scene_change_flag_ = true;
	}
}