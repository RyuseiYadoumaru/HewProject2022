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

	/*	背景初期化	*/
	m_BackGround = make_shared<Actor>("Wall");
#if 1
	//m_BackGround->Vertex("vs_Ui");
	m_BackGround->Sprite("Back_4");
	//m_BackGround->SetSize(1920.0f * 3, 1080.0f * 3);
	Instance(m_BackGround.get());
	m_BackGround->transform->Scale.Set(5.0f, 5.0f, 5.0f);
	m_BackGround->transform->Position.Set((1920.0f / 2.0f) * 3.0f, 1080.0f / 2.0f * 1.8f, 0.0f);

#else
	m_BackGround->Sprite("Living");
	Instance(m_BackGround.get());
	m_BackGround->transform->Scale.Set(5.0f, 5.0f, 10.0f);
	m_BackGround->transform->Position.Set((1920 / 2) * 4, (1080.0f / 2) * 1.7, 0.0f);
#endif // 0

	/*	装飾品	*/
	//窓
	m_Window = make_shared<Actor>("Window");
	m_Window->Sprite("Window");
	Instance(m_Window.get());
	m_Window->transform->Scale.Set(4.5f, 4.5f, 1.0f);
	m_Window->transform->Position.Set(-200.0f, 950.0f, 0.0f);

	//アクアリウム
	m_Aquarium = make_shared<Actor>("Aquarium");
	m_Aquarium->Sprite("Aquarium");
	Instance(m_Aquarium.get());
	m_Aquarium->transform->Position.Set(2750.0f, 750.0f, 0.0f);
	m_Aquarium->transform->Scale.Set(4.5f, 4.5f, 3.0f);

	//ドア
	m_Door = make_shared<Actor>("door");
	m_Door->Sprite("door");
	Instance(m_Door.get());
	m_Door->transform->Position.Set(5500.0f, 950.0f, 0.0f);
	m_Door->transform->Scale.Set(4.5f, 4.5f, 3.0f);

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
	if (m_Player->m_LandTile.GetisLandTile() == false ||
		Input::GetControllerTrigger(XINPUT_GAMEPAD_X))
	{
		m_Map->MoveReset();
	}

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

	/****	背景	****/
	m_BackGround->Render();

	/****	装飾品	****/
	m_Window->Render();
	m_Aquarium->Render();
	m_Door->Render();

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