#include "ProtScene.h"

using namespace GamePlay;
/****	初期化	****/
bool ProtScene::Start()
{
	cout << "プロトタイプシーン" << endl;
	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>("ProtMap");
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");
	m_Fade = make_shared<Fade>("Black");
	m_Table = make_shared<Table>("Table");
	m_AnimTest = make_shared<AnimTest>("Animtest");
	m_Screen = make_shared<ScreenFx>("SFX");
	m_CameraFrame = make_shared<CameraFrame>("CFX");


	/*	インスタンス	*/
	Instance(m_Map.get());
	Instance(m_Player.get());
	Instance(m_BackGruond.get());
	Instance(m_Table.get());
	Instance(m_Fade.get());
	Instance(m_AnimTest.get());
	Instance(m_Screen.get());
	Instance(m_CameraFrame.get());

	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	/*	ギミック初期化	*/
	//個々の部分かなり汚いけど許しておくれ
	m_Player->m_LandTile.Init(m_Player.get(), &m_Map->m_TileColumnList);

	/*　BGＭ再生　*/
	//Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

/****	更新	****/
Scene::STATE ProtScene::Update()
{
	static int cnt = 0;
	cnt++;
	/*	フレームカウント	*/
	cout << "\nフレーム" << cnt << endl;

	/****	ブロック移動	****/
	m_Map->CheckLandTile(&m_Player->m_LandTile);

	/****	オブジェクト更新	****/
	ObjectUpdate();
	m_Fade->Update();

	/****	当たり判定	****/
	m_Map->HitCheckMap(*m_Player);
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Table->GetComponent<BoxCollider2D>());

	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)		//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
}

/****	終了処理	****/
bool ProtScene::End()
{
	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_BGM000);

	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool ProtScene::Render()
{

	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	//m_BackGruond->Render();
	m_Table->Render();
	m_Map->Render();
	m_Player->Render();
	m_AnimTest->Render();

	/****	コライダ描画	****/
	//m_Map->Debug();
	//m_Player->Debug();
	//m_Table->Debug();

	/****	画面エフェクト	****/
	m_Fade->Render();
	m_Screen->Render();
	m_CameraFrame->Render();

	/****	画面描画	****/
	SwapChain();

	return true;
}
