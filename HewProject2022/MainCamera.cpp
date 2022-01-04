#include "MainCamera.h"
#define MOVE_SPEED 20
MainCamera::MainCamera(string in_Name) : Camera(in_Name)
{
	//transform->Position.Set(1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f);
	transform->Position.Set(0.0f, 0.0f, 0.0f);
	p_FocusObject = nullptr;
}
bool MainCamera::Start()
{
	BackgroundColor.Set(32.0f, 56.0f, 96.0f, 1.0f);
	return true;
}

bool MainCamera::Update()
{
	if ((RangeTopLeft.x == 0.0f) &&
		(RangeTopLeft.y == 0.0f) &&
		(RangeButtomRight.x == 0.0f) &&
		RangeButtomRight.y == 0.0f)
	{
		if (p_FocusObject == nullptr)
		{
			if (Input::GetKeyPress(PK_RIGHT)) transform->Position.x += MOVE_SPEED;
			if (Input::GetKeyPress(PK_LEFT)) transform->Position.x -= MOVE_SPEED;
			if (Input::GetKeyPress(PK_DOWN)) transform->Position.y += MOVE_SPEED;
			if (Input::GetKeyPress(PK_UP)) transform->Position.y -= MOVE_SPEED;
		}
		else
		{

			transform->Position.x = p_FocusObject->transform->Position.x;
			transform->Position.y = p_FocusObject->transform->Position.y - 200.0f;
		}
	}

	else if ((RangeTopLeft.x <= transform->Position.x) &&
		(RangeTopLeft.y <= transform->Position.y) &&
		(RangeButtomRight.x >= transform->Position.x) &&
		RangeButtomRight.y >= transform->Position.y)
	{
		if (p_FocusObject == nullptr)
		{
			if (Input::GetKeyPress(PK_RIGHT)) transform->Position.x += MOVE_SPEED;
			if (Input::GetKeyPress(PK_LEFT)) transform->Position.x -= MOVE_SPEED;
			if (Input::GetKeyPress(PK_DOWN)) transform->Position.y += MOVE_SPEED;
			if (Input::GetKeyPress(PK_UP)) transform->Position.y -= MOVE_SPEED;
		}
		else
		{

			transform->Position.x = p_FocusObject->transform->Position.x;
			transform->Position.y = p_FocusObject->transform->Position.y - 200.0f;
		}
	}

	SetCameraPos();
	return true;
}


/****	カメラ描画範囲設定	****/
void MainCamera::Range(Vector2& in_TopLeft, Vector2& in_ButtomRight)
{
	/*	カメラ左上座標	*/
	RangeTopLeft.x = in_TopLeft.x/* + (1920.0f / 2.0f)*/;
	RangeTopLeft.y = in_TopLeft.y/* + (1080.0f / 2.0f)*/;

	/*	カメラ右下座標	*/
	RangeButtomRight.x = in_ButtomRight.x/* - (1920.0f / 2.0f)*/;
	RangeButtomRight.y = in_ButtomRight.y/* - (1080.0f / 2.0f)*/;

}

/****	オブジェクトにフォーカスあてる	****/
void MainCamera::Focus(GameObject* in_Object)
{
	p_FocusObject = in_Object;
}
