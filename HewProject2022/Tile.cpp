#include "Tile.h"
#include"Player.h"

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
		//�F�u���b�N��ޕ���
		SetColorBlock();
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

bool Tile::Update()
{
	/*	�O��̍��W���擾	*/
	m_SavePosition = transform->Position;

	return true;
}

bool Tile::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
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

/****	������瓮���u���b�N�ɕύX����	****/
void Tile::SetColorBlock()
{
	tag = TagList::LandColorBlock;
	switch (m_Kind)
	{
	case LC1:
		m_Kind = C1;
		break;
	case LC2:
		m_Kind = C2;
		break;
	case LC3:
		m_Kind = C3;
		break;
	case LC4:
		m_Kind = C4;
		break;
	default:
		tag = TagList::ColorBlock;
		break;
	}
}

/****	�G�t�F�N�g������	****/
void Tile::EffectInit()
{
	//m_Blockeffect = make_shared<BlockEffect>
	//	(this,
	//		BlockEffect::Color::BLUE,
	//		BlockEffect::EFFECT_KIND::MAGIC);
	//m_Blockeffect->Start();
}


