#include "ScreenFx.h"

ScreenFx::ScreenFx(string in_Name) : Actor(in_Name)
{
}

bool ScreenFx::Start()
{
	/*	スプライト初期化	*/
	m_SpriteRenderer->SpriteName = "sce1";
	m_SpriteRenderer->VertexShaderName = "vs_Ui";
	m_SpriteRenderer->Init();

	/*	座標	*/
	transform->Position.Set(1920.0f / 2, 1080.0f / 2, 0.0f);


	Active = true;

	return true;
}

bool ScreenFx::Update()
{
	return true;
}
