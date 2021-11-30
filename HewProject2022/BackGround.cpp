#include "BackGround.h"

BackGround::BackGround(string in_Name) : Actor(in_Name)
{
}

bool BackGround::Start()
{

	m_SpriteRenderer->SpriteName = "Background";
	transform->Scale.Set(10.0f, 10.0f, 0.0f);
	m_SpriteRenderer->Init();
	/*	背景の左上を座標0にする	*/
	float PosX = m_SpriteRenderer->GetSize().x * transform->Scale.x;
	float PosY = m_SpriteRenderer->GetSize().y * transform->Scale.y;
	//真ん中が中心
	transform->Position.x = PosX;
	transform->Position.x = PosY;
	return true;
}
