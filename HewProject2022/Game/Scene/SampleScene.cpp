#include "SampleScene.h"

using namespace Create;

bool GamePlay::SampleScene::Start()
{
	Hanamaru = make_shared<Test>("はなまる");
	camera = make_shared<Camera>("MainCamera");
	camera->GetBackgroundColor()->Set(0.3f, 1.0f, 0.8f, 1.0f);
	Instance(Hanamaru.get());

	return true;
}


Scene::STATE GamePlay::SampleScene::Update()
{
	camera->Update();

	for (auto i : ObjectArray)
	{
		i.second->Update();
	}

	if (Input::GetKeyTrigger(PK_F2) == true)
	{
		Instance(Hanamaru.get());
	}

	if (Input::GetKeyTrigger(PK_F1) == true)
	{
		Destroy("はなまる");
	}

	return PLAY;
}


bool GamePlay::SampleScene::End()
{
	for (auto i : ObjectArray)
	{
		i.second->End();
	}

	ObjectArray.clear();
	return true;
}

bool GamePlay::SampleScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	Hanamaru->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
