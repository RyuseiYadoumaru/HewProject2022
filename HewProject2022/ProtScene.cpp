#include "ProtScene.h"

using namespace GamePlay;
/****	初期化	****/
bool ProtScene::Start()
{
	cout << "プロトタイプシーン" << endl;
	/*	オブジェクト生成	*/
	m_Map = make_shared<Map>();
	m_Player = make_shared<Player>("Player");
	m_MainCamera = make_shared<MainCamera>("MainCamera");
	m_BackGruond = make_shared<BackGround>("BackGorund");

	Instance(m_Player.get());
	Instance(m_Map.get());
	Instance(m_BackGruond.get());
	/*	カメラ設定	*/
	SetCamera(m_MainCamera.get());
	m_MainCamera->Focus(m_Player.get());

	/*　BGＭ再生　*/
	Sound::Sound_Play(SOUND_LABEL_BGM000);

	return true;
}

/****	更新	****/
Scene::STATE ProtScene::Update()
{
	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****	ブロック移動	****/
	if (Input::GetKeyTrigger(PK_1))
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[24].mp_Column[0];
		m_Map->MoveMap(Debug);
	}

	/*	ブロック挙動	*/
	if (Input::GetKeyTrigger(PK_3) == true && m_Map->GetisMove() == false)
	{
		m_Map->MoveSwicthON();
		Tile* Debug = m_Map->m_TileColumnList[23].mp_Column[0];
		m_Map->MoveMap(Debug);
	}

	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true)//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	マップ当たり判定	****/
	m_Map->HitCheckMap(*m_Player);

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
	m_BackGruond->Render();
	m_Player->Render();
	m_Map->Render();

	/****	コライダ描画	****/
	//m_Map->DebugCollider();
	m_Player->Debug();
	/****	画面描画	****/
	SwapChain();

	return true;
}
