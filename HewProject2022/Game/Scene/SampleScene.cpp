#include "SampleScene.h"

using namespace Create;

bool GamePlay::SampleScene::Start()
{
	Hanamaru = make_shared<Test>("はなまる");
	Teee = make_shared<Test2>("おおおお");
	//Player = Instance<Test>("Player");
	//Block = Instance<Test2>("Block");
	SetCamera();
	camera->GetBackgroundColor()->Set(0.3f, 1.0f, 0.8f, 1.0f);
	Instance(Hanamaru.get());
	Instance(Teee.get());

	return true;
}


Scene::STATE GamePlay::SampleScene::Update()
{

	BoxCollider2D* Col = Hanamaru->GetComponent<BoxCollider2D>();
	BoxCollider2D* Col2 = Teee->GetComponent<BoxCollider2D>();
	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****	システム更新	****/
	SystemUpdate();
	if (Col->HitCheckBox(*Col2))
	{
		Col->PushBackObject();
	}


	//if (Player->GetCollider()->HitCheckBox(*Block->GetCollider()))
	//{
	//	Player->GetCollider()->PushBackObject();
	//}



	//if (Hanamaru->GetCollider()->HitCheckBox(*Teee->GetCollider()))
	//{
	//	Hanamaru->GetCollider()->PushBackObject();
	//}



	camera->Update();

	if (Input::GetKeyTrigger(PK_3) == true)
	{
		ObjectArray.clear();
	}

	if (Input::GetKeyTrigger(PK_F2) == true)
	{
		Instance(Hanamaru.get());
	}

	if (Input::GetKeyTrigger(PK_F1) == true)
	{
		Destroy("はなまる");
	}

	//Hanamaru->GetCollider()->Update();



	return PLAY;
}


bool GamePlay::SampleScene::End()
{
	/****	オブジェクト終了処理	****/
	ObjectEnd();

	delete camera;
	ObjectArray.clear();
	return true;
}

bool GamePlay::SampleScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	//Player->Render();
	//Block->Render();
	//Player->GetCollider()->Debug();
	//Block->GetCollider()->Debug();
	Hanamaru->Render();
	Teee->Render();
	BoxCollider2D* Col = Hanamaru->GetComponent<BoxCollider2D>();
	BoxCollider2D* Col2 = Teee->GetComponent<BoxCollider2D>();
	Col->Debug();
	Col2->Debug();

	/****	画面描画	****/
	SwapChain();

	return true;
}
