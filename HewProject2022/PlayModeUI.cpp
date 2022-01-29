#include "PlayModeUI.h"

PlayModeUI::PlayModeUI(string in_Name) :Actor(in_Name)
{

}

bool PlayModeUI::Start()
{
	m_SpriteRenderer->SpriteName = "GameUI";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	m_SpriteRenderer->Init();

	/*	À•W	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	Active = true;
	return true;
}

bool PlayModeUI::Update()
{
	return true;
}