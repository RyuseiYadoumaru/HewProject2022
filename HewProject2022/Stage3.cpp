#include "Stage3.h"

using namespace Create;

bool GamePlay::Stage3Scene::Start()
{
	/*	インスタンス	*/
	m_Map = Instance<Map>("stage1-2");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_CuhsionStart = Instance<Cuhsion>("CuhsionStart");
	m_SofaEnd = Instance<Sofa>("SofaEnd");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("Wall");
	Instance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("World_obj1_3");
	m_LayerFront = Instance<LayerFront>("LayerFront");
	m_LayerFront->Sprite("World_obj2_1");


	/*	初期化	*/
	m_SofaEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player, &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	return true;
}

Scene::STATE GamePlay::Stage3Scene::Update()
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_CuhsionStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_SofaEnd->GetComponent<BoxCollider2D>());

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

bool GamePlay::Stage3Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage3Scene::Render()
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
	ObjectRender<Cuhsion>("CuhsionStart");
	ObjectRender<Sofa>("SofaEnd");

	ObjectRender<Map>("stage1-2");
	ObjectRender<Player>("Player");

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