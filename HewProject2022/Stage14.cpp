#include "Stage14.h"

using namespace Create;

bool GamePlay::Stage14Scene::Start()
{

	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("MapSizeTest_3");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_Fade = make_shared<Fade>("Black");
	m_RoseStart = make_shared<Rose>("RoseStart");
	m_TreeEnd = make_shared<Tree>("TreeEnd");
	m_ScreenEffect = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	背景初期化	*/
	m_BackGround = make_shared<BackGround>("Wall");
	m_BackGround->Sprite("World3_BG");
	OldInstance(m_BackGround.get());

	m_LayerBack = make_shared<LayerBack>("LayerBack");
	m_LayerBack->Sprite("Wrold3_obj1_3");
	OldInstance(m_LayerBack.get());

	m_LayerFront = make_shared<LayerFront>("LayerFront");
	m_LayerFront->Sprite("Wrold3_obj2_4");
	OldInstance(m_LayerFront.get());

	/*	天井初期化	*/
	m_Ceiling = make_shared<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World2_ceiling");
	OldInstance(m_Ceiling.get());


	/*	インスタンス	*/
	OldInstance(m_Map.get());
	OldInstance(m_Player.get());
	OldInstance(m_RoseStart.get());
	OldInstance(m_TreeEnd.get());
	OldInstance(m_Fade.get());
	OldInstance(m_ScreenEffect.get());
	OldInstance(m_CameraFrame.get());


	/*	初期化	*/
	m_TreeEnd->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*	カメラ設定	*/
	OldSetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	return true;
}

Scene::STATE GamePlay::Stage14Scene::Update()
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_RoseStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_TreeEnd->GetComponent<BoxCollider2D>());

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

bool GamePlay::Stage14Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage14Scene::Render()
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
	m_RoseStart->Render();
	m_TreeEnd->Render();

	m_Map->Render();
	m_Player->Render();

	/****	前装飾品	****/
	m_LayerFront->Render();

	/****	デバッグ	****/
	//m_PlantsEnd->Debug();
	//m_RoseStart->Debug();
	//m_Player->Debug();
	//m_Map->Debug();

	/****	画面エフェクト	****/
	//m_Fade->Render();
	m_ScreenEffect->Render();
	m_CameraFrame->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}