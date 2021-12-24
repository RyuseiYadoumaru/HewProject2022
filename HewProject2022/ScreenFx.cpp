#include "ScreenFx.h"

ScreenFx::ScreenFx(string in_Name) : Actor(in_Name)
{
}

bool ScreenFx::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "sce1";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->Init();
	m_SpriteRenderer->Color.Set(1.0f, 1.0f, 1.0f, 1.0f);

	/*	���W	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);

	return true;
}

bool ScreenFx::Update()
{
	return true;
}
