#include "Chair.h"

Chair::Chair(string in_Name) : Actor(in_Name)
{
}

bool Chair::Start()
{
	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SpriteName = "Chair_4";
	m_SpriteRenderer->Init();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	GameEngine::BoxCollider2D* col = AddComponent<GameEngine::BoxCollider2D>(m_SpriteRenderer->GetSize());
#if 0

	/*	���W�ݒ�	*/
	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(-2480.0f, -520.0f, 0.0f);

	col->SetSize(0.85f, 0.2f);
	col->SetOffset(0.0f, 3.37f);


#else

	transform->Scale.Set(2.0f, 2.0f, 1.0f);
	transform->Position.Set(-2480.0f, -400.0f, 0.0f);

	col->SetSize(0.85f, 0.2f);
	col->SetOffset(0.0f, 2.77f);


#endif // 0


	return true;
}


/****	�f�o�b�O	****/
void Chair::Debug()
{
	GetComponent<GameEngine::BoxCollider2D>()->Debug();
}
