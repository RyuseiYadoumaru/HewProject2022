#include "MainCamera.h"

MainCamera::MainCamera(string in_Name) : Camera(in_Name)
{
	transform->Position.Set(1920.0f / 2.0f, 1080.0f / 2.0f, 0.0f);

}
bool MainCamera::Start()
{
	return true;
}

bool MainCamera::Update()
{
	transform->Position.x = p_FocusObject->transform->Position.x;
	transform->Position.y = p_FocusObject->transform->Position.y;
	SetCameraPos();
	return true;
}



/****	�I�u�W�F�N�g�Ƀt�H�[�J�X���Ă�	****/
void MainCamera::Focus(GameObject* in_Object)
{
	p_FocusObject = in_Object;
}
