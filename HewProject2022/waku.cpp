#include "waku.h"

waku::waku(string in_Name) :Actor(in_Name)
{

}

bool waku::Start()
{
	m_SpriteRenderer->SpriteName = "waku";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->SetSize(1920.0f, 1080.0f);
	m_SpriteRenderer->Init();

	/*	���W	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	Active = true;
	return true;
}

bool waku::Update()
{
	return true;
}