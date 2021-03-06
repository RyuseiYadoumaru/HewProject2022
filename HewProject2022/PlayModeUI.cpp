#include "PlayModeUI.h"
#include "Player.h"
#include "MainCamera.h"

PlayModeUI::PlayModeUI(string in_Name) :Actor(in_Name)
{

}

bool PlayModeUI::Start()
{
	m_SpriteRenderer->SpriteName = "GameUI";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	m_SpriteRenderer->Init();

	/*	???W	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	Active = true;

	m_StarList = Create::Scene::Instance<UI_StarList>("UI_StarList");

	return true;
}

bool PlayModeUI::Update()
{
	if (m_MainCamera->m_CameraMode == false)
	{
		Active = true;
	}
	else
	{
		Active = false;
	}

	return true;
}

bool PlayModeUI::Render()
{
	if (Active == true)
	{
		m_StarList->Render();
		m_SpriteRenderer->Render();
	}
	return true;
}


