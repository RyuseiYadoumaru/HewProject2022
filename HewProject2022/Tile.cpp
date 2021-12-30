#include "Tile.h"


/****	������	****/
bool Tile::Start()
{
	/*	�������W�ۑ�	*/
	m_StartPosition = transform->Position;

	/*	�X�v���C�g������	*/
	m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
	m_SpriteRenderer->Init();

	/*	�{�b�N�X�R���C�_�R���|�[�l���g	*/
	AddComponent<BoxCollider2D>(m_SpriteRenderer->GetSize());

	/*	�^�O�ݒ�	*/
	if (m_Kind != NB && m_Kind != NO && m_Kind != GR)
	{
		tag = ColorBlock;
	}
	else if (m_Kind == NB)
	{
		tag = NormalBlock;
	}
	else if (m_Kind == GR)
	{
		tag = Ground;
	}

	return true;
}

/****	�f�o�b�O�@�\	****/
void Tile::Debug()
{
	GetComponent<BoxCollider2D>()->Debug();	//�����蔻��`��
}

/****	��ގ擾	****/
MAPOBJ Tile::GetKind() const
{
	return m_Kind;
}

/****	��ސݒ�	****/
void Tile::SetKind(MAPOBJ in_MapObj)
{
	m_Kind = in_MapObj;
}

/****	��ݒ�	****/
void Tile::SetColumn(float in_Column)
{
	m_MyColumn = in_Column;
}

/****	�������W�ݒ�	****/
void Tile::SetStartPosition(Vector3& in_Position)
{
	m_StartPosition = in_Position;
}

/****	�������W�擾	****/
Vector3 Tile::GetStartPosition() const
{
	return m_StartPosition;
}

/****	��擾	****/
float Tile::GetMyColumn() const
{
	return m_MyColumn;
}


