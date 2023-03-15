//
// SceneFactory.h
//

#include "Scene/TitleScene.h"
#include "Scene/MainScene.h"
#include "Scene/ClearScene.h"
#include "Scene/GameOverScene.h"

class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	        scene = std::make_unique<TitleScene>();	        break;
		case NextScene::MainScene:	        scene = std::make_unique<MainScene>();	        break;
		case NextScene::ClearScene:			scene = std::make_unique<ClearScene>();			break;
		case NextScene::GameOverScene:		scene = std::make_unique<GameOverScene>();		break;
		}
		return scene;
	}
};