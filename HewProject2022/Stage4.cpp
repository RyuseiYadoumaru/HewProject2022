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
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_TableStart.get());
	Instance(m_TableEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());
	Instance(m_stage4.get());
	Instance(m_world1.get());


	/*	初期化	*/
	m_TableEnd->transform->Position.x = TABLE_DISTANCE;
	m_stage4->transform->Position.Set(0.0f, 0.0f, 0.0f);
	m_world1->transform->Position.Set(-700.0f, -500.0f, 0.0f);

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage4Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	/****	ブロック移動	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);

	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****	当たり判定	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TableStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TableEnd->GetComponent<BoxCollider2D>());


	/****	ロードシーン	****/
	//if (Input::GetKeyTrigger(PK_ENTER) == true ||
	//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
	//{
	//	//GameEngine::SceneManager::LoadScene("ResultScene");
	//}

	/****	システム更新	****/
	m_Map->SystemUpdate();
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
	m_TableStart->Render();
	m_TableEnd->Render();
	m_Map->Render();
	m_Player->Render();
	//m_stage4->Render();
	//m_world1->Render();



	/****	画面エフェクト	****/
	m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();


	/****	画面描画	****/
	SwapChain();

	return true;
}