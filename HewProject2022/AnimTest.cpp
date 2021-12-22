#include "AnimTest.h"
AnimTest::AnimTest(string in_Name) : Character(in_Name)
{
}

bool AnimTest::Start()
{

	transform->Position.Set(-100.0f, 600.0f, 0.0f);

	m_SpriteRenderer->SpriteName = "AnimTest";
	m_SpriteRenderer->Init();

	/*	アニメーションコンポーネント	*/
	AddComponent<Animator>(&P_AnimController);

	return false;
}

bool AnimTest::Update()
{
	if (Input::GetKeyPress(PK_1))
	{
		P_AnimController.AnimState = P_LEFT;
	}
	if (Input::GetKeyPress(PK_2))
	{
		P_AnimController.AnimState = P_RIGHT;
	}
	if (Input::GetKeyPress(PK_3))
	{
		P_AnimController.AnimState = P_UP;
	}
	if (Input::GetKeyPress(PK_4))
	{
		P_AnimController.AnimState = P_DOWN;
	}

	return true;
}
