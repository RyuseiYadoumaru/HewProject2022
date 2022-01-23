#include "TitleScene.h"

using namespace Create;

bool GamePlay::TitleScene::Start()
{

	m_BackGround = Instance<BackGround>("BackGround");
	m_BackGround->Sprite("Title");
	m_BackGround->Vertex("vs_Ui");
	m_BackGround->transform->Position.Set(1920 / 2, 1080 / 2, 0);
	//m_BackGround->transform->Scale.Set(1, 1, 0);
	m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 0;


	//オブジェクト生成 初期化

	/**** タイトル・チームロゴ初期化 ****/
	m_Title = Instance<Title>("TitleText");
	m_Title->Sprite("TitleLogo");
	m_Title->transform->Position.y -= 120;

	m_TeamLogo = Instance<Title>("TeamLogo");
	m_TeamLogo->Sprite("TeamLogo");
	m_TeamLogo->transform->Scale.Set(0.8, 0.8, 0);

	m_PushAny = Instance<PushAny>("PushAny");
	m_PushAny->Sprite("Any");
	m_PushAny->transform->Position.y -= 100;
	m_PushAny->transform->Scale.Set(1.1, 1.1, 0);

	m_GameEnd = Instance<Actor>("GameEnd");
	m_GameEnd->Sprite("End");
	m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
	m_GameEnd->Vertex("vs_Ui");
	m_GameEnd->transform->Position.Set(1920 / 2, 1080 / 2, 0);
	m_GameEnd->transform->Scale.Set(1.5, 1.5, 0);

	m_EndCursor = Instance<Actor>("EndCursor");
	m_EndCursor->Sprite("button");
	m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
	m_EndCursor->Vertex("vs_Ui");
	m_EndCursor->transform->Position.Set(1920 / 2, 1080 / 2, 0);


	/*	カメラ設定	*/
	SetCamera();
	camera->GetBackgroundColor()->Set(1.0f, 1.0f, 1.0f, 1.0f);

	EndWin_flg = false;
	End_flg = false;

	return true;
}

Scene::STATE GamePlay::TitleScene::Update()
{


	/****	オブジェクト更新	****/
	ObjectUpdate();

	/****  ロゴ表示  ****/
	if (m_TeamLogo->GetLogo_sw() == true) {
		m_TeamLogo->Fade_Switch();
	}
	else if (m_TeamLogo->GetLogo_sw() == false)
	{
		m_BackGround->GetComponent<SpriteRenderer>()->Color.a = 1;
		m_Title->Fade_In();
		//点滅処理
		m_PushAny->Flashing();
		/**  ゲーム終了用分岐  **///クラスにまとめると何故かエラー吐くので直で書きました。（クラスにまとめれそうならまとめてほしいなぁ…）
		if (EndWin_flg == false) {//通常状態
			End_flg = false;
			if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN) == true)//Ａボタンでワールドセレクトへ
			{
				Input::Vibration(XINPUT_GAMEPAD_RIGHT_VIBRATION_MAX, 750.0f);
				GameEngine::SceneManager::LoadScene("WorldSelectScene");
			}
			if (Input::GetControllerTrigger(XINPUT_GAMEPAD_B) == true || Input::GetKeyTrigger(VK_ESCAPE)) {//スタートボタンでゲーム終了ウインドウの表示
				//ゲーム終了ウインドウを表示する
				m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 1;
				m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 1;
				EndWin_flg = true;//ゲーム終了準備状態へ
			}
		}
		else {//ゲーム終了準備
			if (m_GameEnd->GetComponent<SpriteRenderer>()->Color.a == 1) {
				if (End_flg == false) {//カーソル位置が「いいえ」の時
					m_EndCursor->transform->Position.Set((1920.0f / 2.0f) - 120, (1080.0f / 2.0f) + 80, 0.0f);
					/*if (Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true) {
						End_flg = true;
					}*/
					if (Input::GetControllerLeftStick().y > 0.5 || Input::GetKeyTrigger(VK_DOWN) || Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true) {//スティックを下に倒したときの判定
						End_flg = true;//true=(ゲーム終了)
					}

				}
				else {//カーソル位置が「はい」の時
					m_EndCursor->transform->Position.Set((1920.0f / 2.0f) - 120, (1080.0f / 2.0f) + 150 + 80, 0.0f);
					/*if (Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true) {
						End_flg = false;
					}*/
					if (Input::GetControllerLeftStick().y < -0.5 || Input::GetKeyTrigger(VK_UP) || Input::GetControllerTrigger(XINPUT_GAMEPAD_DPAD_UP) == true) {//スティックを上に倒したときの判定
						End_flg = false;//false=(そのまま)
					}

				}
				//ゲーム終了選択
				if (Input::GetControllerPress(XINPUT_GAMEPAD_A) == true || Input::GetKeyTrigger(VK_RETURN)) {//はい（ゲームを終了）
					if (End_flg == true) {
						Application::Instance()->isEnd = true;//Engineのループ停止
					}
					if (End_flg == false) {//いいえ（ゲームタイトルに戻る）
						//ゲーム終了ウインドウを非表示にする
						m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
						m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
						EndWin_flg = false;//通常状態へ
					}
				}
				else if (Input::GetKeyTrigger(VK_ESCAPE))
				{
					m_GameEnd->GetComponent<SpriteRenderer>()->Color.a = 0;
					m_EndCursor->GetComponent<SpriteRenderer>()->Color.a = 0;
					EndWin_flg = false;//通常状態へ
				}
			}
		}
	}

	///****	NextScene	****/
	//if (Input::GetControllerTrigger(XINPUT_GAMEPAD_A) == true ||
	//	Input::GetKeyTrigger(PK_ENTER) == true)
	//{
	//	Input::Vibration(XINPUT_GAMEPAD_RIGHT_VIBRATION_MAX, 750.0f);
	//	GameEngine::SceneManager::LoadScene("WorldSelectScene");
	//}



	/****	システム更新	****/
	SystemUpdate();
	return PLAY;
}

bool GamePlay::TitleScene::End()
{
	/*	オブジェクト終了処理	*/
	ObjectEnd();

	/*	解放処理	*/
	Releace();

	return true;
}

bool GamePlay::TitleScene::Render()
{
	/****	画面クリア	****/
	ClearDisplay();

	/****	オブジェクト描画	****/
	ObjectRender<BackGround>("BackGround");
	ObjectRender<Title>("TitleText");
	ObjectRender<PushAny>("PushAny");
	ObjectRender<Title>("TeamLogo");
	ObjectRender<Actor>("GameEnd");
	ObjectRender<Actor>("EndCursor");
	/****	画面描画	****/
	SwapChain();

	return true;
}