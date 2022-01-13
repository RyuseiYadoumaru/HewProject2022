#include "Stage1.h"

using namespace Create;

bool GamePlay::Stage1Scene::Start()
{

	/*	オブジェクト生成	*/
	//m_Map =				make_shared<Map>("stage1-1");
	//m_Player =			make_shared<Player>("Player");
	//m_MainCamera =		make_shared<MainCamera>("MainCamera");
	//m_Fade =				make_shared<Fade>("Black");
	//m_TableStart =		make_shared<Table>("TableStart");
	//m_SofaEnd =			make_shared<Sofa>("SofaEnd");
	//m_ScreenEffect =		make_shared<ScreenFx>("SFX");
	//m_CameraFrame =		make_shared<CameraFrame>("CFX");
	//m_BigBook =			make_shared<BigBook>("Book1");
	//m_MiniBook =			make_shared<MiniBook>("Book2");

	///*	背景初期化	*/
	//m_BackGround = make_shared<BackGround>("Wall");
	//m_BackGround->Sprite("Wall");
	//OldInstance(m_BackGround.get());

	//m_LayerBack = make_shared<LayerBack>("LayerBack");
	//m_LayerBack->Sprite("World_obj1_1");
	//OldInstance(m_LayerBack.get());

	//m_LayerFront = make_shared<LayerFront>("LayerFront");
	//m_LayerFront->Sprite("World_obj2_1");
	//OldInstance(m_LayerFront.get());

	///*	天井初期化	*/
	//m_Ceiling = make_shared<Ceiling>("Ceiling");
	//m_Ceiling->Sprite("ceiling");
	//OldInstance(m_Ceiling.get());


	/*	インスタンス	*/
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_TableStart = Instance<Table>("TableStart");
	m_SofaEnd = Instance<Sofa>("SofaEnd");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BigBook = Instance<BigBook>("Book1");
	m_MiniBook = Instance<MiniBook>("Book2");

	/*	背景初期化	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_1");

	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_1");

	/*	天井初期化	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("ceiling");

	//OldInstance(m_Map.get());
	//OldInstance(m_Player.get());
	//OldInstance(m_TableStart.get());
	//OldInstance(m_SofaEnd.get());
	//OldInstance(m_Fade.get());
	//OldInstance(m_ScreenEffect.get());
	//OldInstance(m_CameraFrame.get());
	//OldInstance(m_BigBook.get());
	//OldInstance(m_MiniBook.get());

	/*	初期化	*/
	m_SofaEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player, &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	return true;
}

Scene::STATE GamePlay::Stage1Scene::Update()
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TableStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaEnd->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_BigBook->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_MiniBook->GetComponent<BoxCollider2D>());


	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)
	{
		GameEngine::SceneManager::LoadScene("Stage2");
	}

	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();	return PLAY;
}

bool GamePlay::Stage1Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage1Scene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	背景	****/
	ObjectRender<BackGround>("Wall");

	/****	後装飾品	****/
	ObjectRender<LayerBack>("LayerBack");

	/****	天井	****/
	ObjectRender<Ceiling>("Ceiling");

	/****	オブジェクト描画	****/
	ObjectRender<Player>("Player");
	ObjectRender<Map>("stage1-1");
	ObjectRender<Table>("TableStart");
	ObjectRender<Sofa>("SofaEnd");
	ObjectRender<BigBook>("Book1");
	ObjectRender<MiniBook>("Book2");

	/****	前装飾品	****/
	ObjectRender<LayerFront>("LayerFront");

	/****	デバッグ	****/
	//m_Player->Debug();
	//m_Map->Debug();
	//m_TableStart->Debug();

	/****	画面エフェクト	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/****	画面描画	****/
	SwapChain();

	return true;
}