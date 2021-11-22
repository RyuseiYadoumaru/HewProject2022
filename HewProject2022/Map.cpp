#include "Map.h"
using Math::Vector3;

#pragma region Debug

static char DebugMap[MAPSIZE_HEIGHT][MAPSIZE_WIDTH]
{
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,CB,CB,CB,CB,CB,CB,CB,CB,CB,CB,CB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,CB,NB,NB,NB,CB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,CB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,CB,CB,CB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,CB,NO,NB,NO,CB,NO,NO,NO,NO,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NB,NO,NB,NO,NB,NO,CB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NB,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NO,NB,NB,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB},
	{NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NO,NO,NO,NO,NO,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB,NB}
};
#pragma endregion static char DebugMap(�f�o�b�O�p)

Map::Map()
{
	m_MapChip = &DebugMap[0][0];
	m_Speed = 10.0f;
}

bool Map::Start()
{
	Vector2 Pos;
	Vector2 Cell;
	for (int y = 0; y < MAPSIZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAPSIZE_WIDTH; x++)
		{
			/****	���W�ݒ�	****/
			float PosX = TILE_WIDTH * x;
			float PosY = TILE_HEIGHT * y;
			Pos.Set(PosX, PosY);				//���ݍ��W�ݒ�
			Cell.Set((float)x, (float)y);		//���݃Z���ݒ�

			switch (m_MapChip[MAPSIZE_WIDTH * y + x])
			{
			case NB:
				CreateTile(Pos, Cell, "NormalBlock", MAPOBJ::NB);
				break;

			case CB:
				CreateTile(Pos, Cell, "ColorBlock", MAPOBJ::CB);
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}

	return true;
}

bool Map::Update()
{
	for (auto Tile : m_TileList)
	{
		Tile.second->Update();
	}
	return true;
}

bool Map::End()
{
	return true;
}

bool Map::Render()
{
	for (auto Tile : m_TileList)
	{
		Tile.second->Render();
	}
	return true;
}

/****	�}�b�v����	****/
bool Map::MoveMap(Vector2& in_Cell)
{
	//��u���b�N�����߂�


	//�ړ����������߂�
	SelectMoveCell();

	//�ړ��ʐݒ�
	SetCellVector();

	//���߂�ꂽ�u���b�N���ړ�����
	MoveTile();
	//

	return true;
}

/****	�^�C������	****/
void Map::CreateTile(Vector2& in_Position, Vector2& Cell, string FileName, MAPOBJ in_MapObj)
{
	/*	�}�b�vKey�𐶐�	*/
	float i = Cell::GetCellAddress(Cell, (float)MAPSIZE_WIDTH);

	m_TileList.insert(make_pair(i, make_shared<Tile>()));
	m_TileList[i]->transform.Position.Set(in_Position.x, in_Position.y, 0.0f);
	m_TileList[i]->Sprite(FileName);
	m_TileList[i]->Start();
	m_TileList[i]->SetCell(Cell.x, Cell.y);
	m_TileList[i]->SetKind(in_MapObj);

}

/****	�ړ����������߂�	****/
bool Map::SelectMoveCell()
{
	//��u���b�N�����߂�
	m_MoveCellList.push_back(25.0f);
	m_MoveCellList.push_back(26.0f);
	m_MoveCellList.push_back(27.0f);
	m_MoveCellList.push_back(28.0f);

	return true;
}

/****	�ړ��x�N�g��	****/
void Map::SetCellVector()
{
	/*	��u���b�N�Z��	*/
	Vector2 TargetCell;
	TargetCell.x = 25.0f;
	TargetCell.y = 10.0f;

	m_TargetCell.SetDefault(TargetCell.x, TargetCell.y);

	//��Z���̃A�h���X�擾
	float TargetCellAddress = Cell::GetCellAddress(TargetCell, MAPSIZE_WIDTH);

	for (auto CellX : m_MoveCellList)
	{
		for (int y = 0; y < MAPSIZE_HEIGHT; y++)
		{
			//�T�����Z���̃A�h���X
			Vector2 NowCell;
			NowCell.x = CellX;			//��(MoveCellList�̗���Q�Ƃ���)
			NowCell.y = (float)y;		//�s

			/*	���݂̃Z���A�h���X�擾	*/
			float NowCellAddress = Cell::GetCellAddress(NowCell, MAPSIZE_WIDTH);

			/*	�Z�����Ȃ����@&& �F�u���b�N�̎�	*/
			if (m_TileList.count(NowCellAddress) == true && m_TileList[NowCellAddress]->GetKind() == CB)
			{
				/*	�ړ��ʐݒ�	*/
				// �ڕW���W = �ڕW�u���b�NY���W - ���݃u���b�NY���W
				float TargetPosY = m_TileList[TargetCellAddress]->transform.Position.y - m_TileList[NowCellAddress]->transform.Position.y;

				/*	�ړ��ʕۑ�	*/
				//�񂲂Ƃ̈ړ��ʂ�ۑ�����
				m_CellVectorY.insert(make_pair(CellX, TargetPosY));
				//�J���[�u���b�N�̍��W��ۑ����Ă���
				//m_StandardColorTileList.insert(NowCellAddress, m_TileList[NowCellAddress].get());

			}


		}


	}
}

/****	�I�u�W�F�N�g�ړ�����	****/
void Map::MoveTile()
{
	for (auto CellX : m_MoveCellList)
	{

		/*	�ړ���̃u���b�N�T��	*/
		for (int y = 0; y < MAPSIZE_HEIGHT; y++)
		{
			//�T�����Z���̃A�h���X
			Vector2 NowCell;
			NowCell.x = CellX;			//��(MoveCellList�̗���Q�Ƃ���)
			NowCell.y = (float)y;		//�s

			float NowCellAddress = Cell::GetCellAddress(NowCell, MAPSIZE_WIDTH);

			/*	�J���[�u���b�N����	*/
			//�J���[�u���b�N���^�[�Q�b�g���W�Ɠ�������
			//������ړ��̈ړ��C�������Ή����Ă��Ȃ�
			//�������̈ړ��Ń^�[�Q�b�g���W�𒴂����Ƃ��̏����������I�I�I�I�I
			if (true/*	�J���[�u���b�N�̍��W != ��u���b�N�̍��W	*/)
			{
				/*	�u���b�N�x�N�g���쐬	*/
				float VectorY = (m_MoveCellList[NowCell.x] * m_Speed) / fabs(m_CellVectorY[NowCell.x]);
				float TargetCellAddress = m_TargetCell.GetDefaultAddress(MAPSIZE_WIDTH);
				/*	�ړ��ʊm��	*/
				//Tile* ColorTile =


					/*	�Z��������Ƃ�	*/
				if (m_TileList.count(NowCellAddress) == true)
				{
					/*	�ړ�����������	*/

					//Y���W�Ƀx�N�g�������Z����
					float NextPosY = m_TileList[NowCellAddress]->transform.Position.y + VectorY;

					m_TileList[NowCellAddress]->transform.Position.y = NextPosY;
					/*	�ړ��C��	*/
					//if (m_TileList[NowCellAddress]->transform.Position.y <= )

				}

			}
		}
	}

}
