//
// SceneFactory.h
//

#include "TitleScene.h"
#include "MainScene.h"
#include "BossTestScene.h"
#include "ResultScene.h"

class SceneFactory final {
public:
	static std::unique_ptr<Scene> CreateScene(const NextScene nextScene)
	{
		std::unique_ptr<Scene> scene;
		switch (nextScene) {
		case NextScene::TitleScene:	        scene = std::make_unique<TitleScene>();	        break;
		case NextScene::MainScene:	        scene = std::make_unique<MainScene>();	        break;
		case NextScene::BossTestScene:		scene = std::make_unique<BossTestScene>();		break;
		case NextScene::ResultScene:		scene = std::make_unique<ResultScene>();		break;
		}
		return scene;
	}
};