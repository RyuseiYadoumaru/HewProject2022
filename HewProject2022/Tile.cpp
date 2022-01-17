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

	/*	�G�t�F�N�g������	*/
	EffectInit();

	return true;
}

bool Tile::Update()
{
	/*	�O��̍��W���擾	*/
	m_SavePosition = transform->Position;

	/*	����ւ�����	*/
	//�������R�����g�A�E�g����Ɠ���ւ������؂�܂��B
	//Replacement();

	return true;
}

bool Tile::Render()
{
	if (Active == true)
	{
		m_SpriteRenderer->Render();
		//m_Blockeffect->Render();
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

/****	����ւ�����	****/
void Tile::Replacement()
{
	//�v���C���[��NB�܂���GR�ɏ���Ă���Ƃ��͐F���ς��
	Player* m_Player = Create::Scene::GetGameObject<Player>("Player");

	//����GetKind()��NULL��������return
	/*if (m_Player->m_LandTile->GetLandTile() == LandGround) {

		return;
	}*/
	//else if�����������ւ��
	if (m_Player->m_LandTile->GetLandTile() == LandGround || m_Player->m_LandTile->GetLandTile()->GetKind() == NB)
	{

		//�^�C�}�[�Ƀf���^�^�C�����Z
		m_ReplacementTimer += GameTimer::deltaTime();

		if (m_ReplacementTimer >= REPLACEMENT_TIME) {//3�b�o�߂���ƐF���ς��

			switch (this->m_Kind) {
				{
			case RED_BLOCK:
				this->m_Kind = BLUE_BLOCK;
				//�����ɓ����Ă���摜�����폜���āA�V�����摜����}������?
				//�폜���Ă��Ȃ��ł��@2022/01/12
				this->Sprite("blue");
				break;

			case BLUE_BLOCK:
				this->m_Kind = GREEN_BLOCK;
				this->Sprite("green");
				break;

			case GREEN_BLOCK:
				this->m_Kind = PARPLE_BLOCK;
				this->Sprite("purple");
				break;

			case PARPLE_BLOCK:
				this->m_Kind = RED_BLOCK;
				this->Sprite("red");
				break;

				}
			}
			//�摜�̃T�C�Y���ύX���Ȃ��Ƃ����Ȃ�
			this->m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
			this->m_SpriteRenderer->Init();

			//�^�C�}�[���O�ɖ߂�
			m_ReplacementTimer = 0;
		}


		//�ȉ�����ւ��u���b�N�ǉ���̎���

		/*
		//�^�C�}�[�Ƀf���^�^�C�����Z
		m_ReplacementTimer += GameTimer::deltaTime();

		if (m_ReplacementTimer >= REPLACEMENT_TIME) {

			switch (this->m_Kind) {
				{
			case REPLACEMWNT_RED_BLOCK:
				this->m_Kind = REPLACEMWNT_BLUE_BLOCK;
				//�����ɓ����Ă���摜�����폜���āA�V�����摜����}������?
				//�폜���Ă��Ȃ��@2022/01/12
				this->Sprite("blue");
				break;

			case REPLACEMWNT_BLUE_BLOCK:
				this->m_Kind = REPLACEMWNT_GREEN_BLOCK;
				this->Sprite("green");
				break;

			case REPLACEMWNT_GREEN_BLOCK:
				this->m_Kind = REPLACEMWNT_PURPLE_BLOCK;
				this->Sprite("purple");
				break;

			case REPLACEMWNT_PURPLE_BLOCK:
				this->m_Kind = REPLACEMWNT_RED_BLOCK;
				this->Sprite("red");
				break;

				}
			}
			//�摜�̃T�C�Y���ύX���Ȃ��Ƃ����Ȃ�
			this->m_SpriteRenderer->SetSize(TILE_WIDTH, TILE_HEIGHT);
			this->m_SpriteRenderer->Init();

			//�^�C�}�[���O�ɖ߂�
			m_ReplacementTimer = 0;
		}
		*/
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


