#include "Title.h"

Title::Title(string in_Name) : Actor(in_Name)
{
}

bool Title::Start()
{
	//Now_Scene = "TitleScene";
	m_SpriteRenderer->Init();
	this->Vertex("vs_Ui");										//画面座標の取得
	this->transform->Position.Set(1920 / 2, (1080 / 2) - 70, 0);	//座標初期値設定
	this->GetComponent<SpriteRenderer>()->Color.a = 0;			//初期で非表示に
	Logo_sw = true;												//フラグの初期化
	Frame_cnt = 0.0f;
	nowTime = 0.0f;
	return true;
}

bool Title::Fade_In()
{

	//α値を上げていく
	if (this->GetComponent<SpriteRenderer>()->Color.a < 1.0f) {
		this->GetComponent<SpriteRenderer>()->Color.a += 0.008f;
	}
	return true;
}

bool Title::Fade_Out()
{
	//α値を下げていく
	if (this->GetComponent<SpriteRenderer>()->Color.a > 0.0f) {
		this->GetComponent<SpriteRenderer>()->Color.a -= 0.008f;
	}
	return true;
}

bool Title::Fade_Switch()
{
	//フレームカウントでフェードイン・フェードアウトを切替
	Frame_cnt++;

	//デルタタイム加算
	nowTime += GameTimer::deltaTime();

	/****	タイトルフェードアニメーション	****/
	if (nowTime > fadeTime)
	{
		if (GameTimer::ErrorFPS() == false)
		{
			//FPSが安定したらフェードアウトを行う
			this->Fade_Out();
		}
	}

	else
	{
		//フェードイン
		this->Fade_In();
	}


	//if (GameTimer::ErrorFPS() == true)
	//{
	//	if (Frame_cnt < 500) 
	//	{
	//		this->Fade_In();
	//	}
	//	else if (Frame_cnt >= 500 && GameTimer::ErrorFPS() == false) {
	//		this->Fade_Out();
	//	}

	//}

	//else
	//{
	//	if (Frame_cnt < 60) {
	//		this->Fade_In();
	//	}
	//	else if (Frame_cnt >= 60) {
	//		this->Fade_Out();
	//	}
	//}
	if (this->GetComponent<SpriteRenderer>()->Color.a <= 0) {
		Logo_sw = false;//フラグ切替（タイトルシーンのフラグ切替）
	}
	return true;
}

//フラグの取得
bool Title::GetLogo_sw()
{
	return Logo_sw;
}
