#include "MainCamera.h"

MainCamera::MainCamera(string in_Name) : Camera(in_Name)
{
	transform->Position.Set(1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f);
	p_FocusObject = nullptr;
}
bool MainCamera::Start()
{
	BackgroundColor = Math::Color::Gray;
	return true;
}

bool MainCamera::Update()
{
	if (p_FocusObject == nullptr)
	{
		if (Input::GetKeyPress(PK_RIGHT)) transform->Position.x += 10;
		if (Input::GetKeyPress(PK_LEFT)) transform->Position.x -= 10;
		if (Input::GetKeyPress(PK_DOWN)) transform->Position.y += 10;
		if (Input::GetKeyPress(PK_UP)) transform->Position.y -= 10;
	}
	else
	{

		transform->Position.x = p_FocusObject->transform->Position.x;
		transform->Position.y = p_FocusObject->transform->Position.y - 200.0f;
	}
	SetCameraPos();
	return true;
}



/****	オブジェクトにフォーカスあてる	****/
void MainCamera::Focus(GameObject* in_Object)
{
	p_FocusObject = in_Object;
}
