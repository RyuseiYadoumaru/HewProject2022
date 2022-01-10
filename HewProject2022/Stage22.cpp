#include "Stage22.h"

using namespace Create;

bool GamePlay::Stage22Scene::Start()
{

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_StorageStart = make_shared<Storage>("StorageStart");
	m_HouseEnd = make_shared<House>("HouseEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	背景初期化	*/
	m_BackGround = make_shared<BackGround>("Wall");
	m_BackGround->Sprite("World5_BG");
	Instance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World5_obj1_1");
	Instance(m_LayerBack.get());

	m_LayerFront = make_shared<LayerFront>("LayerFront");
	//m_LayerFront->Sprite("Wrold5_obj2_1");
	Instance(m_LayerFront.get());

	/*	天井初期化	*/
	m_Ceiling = make_shared<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World2_ceiling");
	Instance(m_Ceiling.get());


	/*	インスタンス	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_StorageStart.get());
	Instance(m_HouseEnd.get());
	Instance(m_Fade.get());
	Instance(m_ScreenEffect.get());
	Instance(m_CameraFrame.get());


	/*	初期化	*/
	m_HouseEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	//m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage22Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	/****	ブロック移動	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);
	if (((m_Player->m_LandTile.GetisLandTile() == false) ||
		(Input::GetControllerTrigger(XINPUT_GAMEPAD_X)) || Input::GetKeyTrigger(PK_R)) &&
		(m_Map->m_OnReset == false))
	{
		//リセット発動
		m_Map->m_OnReset = true;
	}

	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****	当たり判定	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_StorageStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_HouseEnd->GetComponent<BoxCollider2D>());

	/****	ロードシーン	****/
	//if (Input::GetKeyTrigger(PK_ENTER) == true ||
	//	Input::GetControllerTrigger(XINPUT_GAMEPAD_A))
	//{
	//	//GameEngine::SceneManager::LoadScene("ResultScene");
	//}

	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();	return PLAY;
}

bool GamePlay::Stage22Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage22Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	m_BackGround->Render();

	/****	後装飾品	****/
	m_LayerBack->Render();

	/****	天井	****/
	m_Ceiling->Render();

	/****	オブジェクト描画	****/
	m_StorageStart->Render();
	m_HouseEnd->Render();

	m_Map->Render();
	m_Player->Render();

	/****	前装飾品	****/
	m_LayerFront->Render();

	/****	デバッグ	****/
	m_HouseEnd->Debug();
	m_Map->Debug();
	//m_RoseStart->Debug();
	//m_Player->Debug();

	/****	画面エフェクト	****/
	//m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}