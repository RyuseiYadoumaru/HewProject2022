#include "Stage4.h"

using namespace Create;

bool GamePlay::Stage4Scene::Start()
{
	cout << "１－４ゲームシーン" << endl;

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("ProtMap");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_TableStart = make_shared<Table>("TableStart");
	m_TableEnd = make_shared<Table>("TableEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	//オブジェクト生成 初期化
	m_stage4 = make_shared<Actor>("Stage-04");
	m_world1 = make_shared<Actor>("World-01");
	m_stage4->Sprite("stage-04");
	m_world1->Sprite("world-01");

	/*	インスタンス	*/
	Instance(m_stage4.get());
	Instance(m_world1.get());

	m_stage4->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);
	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

Scene::STATE GamePlay::Stage4Scene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();


	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage4Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage4Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	m_stage4->Render();
	m_world1->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}