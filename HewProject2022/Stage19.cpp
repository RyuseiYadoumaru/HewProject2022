#include "Stage19.h"

using namespace Create;

bool GamePlay::Stage19Scene::Start()
{
	/* インスタンス */
	m_Map = Instance<Map>("stage1-1");
	m_Player = Instance<Player>("Player");
	m_MainCamera = Instance<MainCamera>("MainCamera");
	m_Fade = Instance<Fade>("Black");
	m_ScreenEffect = Instance<ScreenFx>("SFX");
	m_CameraFrame = Instance<CameraFrame>("CFX");
	m_PicTureFrameStart = Instance<PictureFrame>("PicTureFrameStart");
	m_Shelf2End = Instance<Shelf2>("Shelf2End");

	/*	背景初期化	*/
	m_BackGround = Instance<BackGround>("Wall");
	m_BackGround->Sprite("WORLD4_BG");

	m_LayerBack = Instance<LayerBack>("LayerBack");
	m_LayerBack->Sprite("world4_obj1_4");

	/*	天井初期化	*/
	m_Ceiling = Instance<Ceiling>("Ceiling");
	m_Ceiling->Sprite("World4_Ceiling");

	/*	初期化	*/
	m_Shelf2End->transform->Position.x += ROAD_DISTANCE;

	/*	ギミック初期化	*/


	/*	カメラ設定	*/
	SetCamera(m_MainCamera);
	m_MainCamera->Focus(m_Player);

	return true;
}

Scene::STATE GamePlay::Stage19Scene::Update()
{
	/*	フレームカウント	*/
	static int cnt = 0;
	cnt++;
	cout << "\nフレーム" << cnt << endl;

	/****	ブロック移動	****/
	m_Map->CheckLandTile(m_Player->m_LandTile);
	if (((m_Player->m_LandTile->GetisLandTile() == false) ||
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
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_PicTureFrameStart->GetComponent<BoxCollider2D>());
	m_Player->GetComponent<BoxCollider2D>()->HitCheckBox(*m_Shelf2End->GetComponent<BoxCollider2D>());

	/****	ロードシーン	****/
	if (Input::GetKeyTrigger(PK_ENTER) == true || Input::GetControllerTrigger(XINPUT_GAMEPAD_B))//エンター押すと次のシーンへ移動
	{
		GameEngine::SceneManager::LoadScene("ResultScene");
	}

	/****	システム更新	****/
	m_Map->SystemUpdate();
	SystemUpdate();
	return PLAY;
}

bool GamePlay::Stage19Scene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::Stage19Scene::Render()
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
	ObjectRender<PictureFrame>("PicTureFrameStart");
	ObjectRender<Shelf2>("Shelf2End");

	/****	画面エフェクト	****/
	//m_Fade->Render();
	ObjectRender<ScreenFx>("SFX");
	ObjectRender<CameraFrame>("CFX");

	/****	画面描画	****/
	SwapChain();

	return true;
}