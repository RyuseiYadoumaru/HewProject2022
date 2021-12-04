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


	/****	マップ当たり判定	****/
	m_Map->HitCheckMap(*m_Player);

	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

/****	終了処理	****/
bool ProtScene::End()
{
	/*	サウンドストップ	*/
	Sound::Sound_Stop(SOUND_LABEL_BGM000);
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
	m_Map->DebugCollider();
	m_Player->Debug();
	/****	画面描画	****/
	SwapChain();

	return false;
}
