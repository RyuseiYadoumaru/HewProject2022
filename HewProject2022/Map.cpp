#include "Map.h"
#include "Engine/Create/Scene.h"
using Math::Vector3;


Map::Map()
{
	m_MapDataName = "ProtMap";
	m_isMove = false;
	m_isReturnMove = false;
	m_MoveTime = 100.0f / 100.0f;
}

Map::Map(std::string in_MapDataName) : GameObject(in_MapDataName)
{
	m_MapDataName = in_MapDataName;
	m_isMove = false;
	m_isReturnMove = false;
	m_MoveTime = 100.0f / 100.0f;


}

/****	������	****/
bool Map::Start()
{
	/*	�}�b�v���[�h	*/
	m_Mapdata.Load(m_MapDataName);

	/*	�}�b�v����	*/
	CreateMap();

	return true;
}

/****	�X�V	****/
bool Map::Update()
{
	/*	�}�b�v�ړ�����	*/
	if (m_isMove == true)
	{
		//�t���O��true�̂Ƃ��ړ�����
		MoveTile();
	}

	/*	�}�b�v�ړ���߂�����	*/
	if (m_isReturnMove == true)
	{
		ReturnMoveColumn();
	}

	/*	Transform�X�V	*/
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		for (auto now : m_TileColumnList[Column].mp_Column)
		{
			now->transform->Update();
		}
	}
	return true;
}

/****	�I������	****/
bool Map::End()
{
	for (auto List : m_TileColumnList)
	{
		List.Clear();
	}
	return true;
}

bool Map::Render()
{

	Create::Camera* camera = Create::Scene::GetCamera();
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		for (auto now : m_TileColumnList[Column].mp_Column)
		{
			if (now->transform->Position.x >= camera->GetLeft() - 100.0f&& now->transform->Position.x <= camera->GetRight() + 100.0f &&
				now->transform->Position.y >= camera->GetTop() - 100.0f && now->transform->Position.y <= camera->GetButtom() + 100.0f)
			{
				now->Render();

			}
		}
	}
	return true;
}

/****	�}�b�v�����蔻��	****/
bool Map::HitCheckMap(GameObject& in_GameObject)
{
	/*	�q�b�g�`�F�b�N�I�u�W�F�N�g	*/
	BoxCollider2D* CheckObject = in_GameObject.GetComponent<BoxCollider2D>();
	Create::Camera* camera = Create::Scene::GetCamera();
	/*	�����蔻��	*/
	for (int column = 0; column < m_Mapdata.GetSize().x; ++column)
	{
		TileColumn& Search = m_TileColumnList[column];
		for (auto NowTile : Search.mp_Column)
		{
			BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
			if (NowTile->transform->Position.x >= camera->GetLeft() && NowTile->transform->Position.x <= camera->GetRight() &&
				NowTile->transform->Position.y >= camera->GetTop() && NowTile->transform->Position.y <= camera->GetButtom())
			{
				CheckObject->HitCheckBox(*TileCol);
			}

		}
	}

	return true;

}

/****	�}�b�v����	****/
bool Map::MoveMap(Tile* in_StandardTile)
{
	if (m_MoveFrontColumnList.empty() == false)
	{
		Log::LogError("Error MoveMap Function");
		return false;
	}

	/*	���ʂ̃u���b�N�ɏ������	*/
	if (in_StandardTile->GetKind() == NB)
	{
		//���ɖ߂�����
		cout << "���Z�b�g�����J�n" << endl;
		SetSaveColumn();
		m_isReturnMove = true;
		return true;
	}

	/*	�ړ��u���b�N����	*/
	m_SaveMoveColumnList.clear();
	SetMoveFrontColumn(*in_StandardTile);	//�O
	SetMoveBackColumn(*in_StandardTile);	//��

	return true;
}

/****	�R���C�_�`��	****/
void Map::DebugCollider()
{
	/*	�`��	*/
	for (int column = 0; column < m_Mapdata.GetSize().x; ++column)
	{
		TileColumn& Search = m_TileColumnList[column];
		for (auto NowTile : Search.mp_Column)
		{
			NowTile->Debug();
		}
	}
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	�}�b�v��������	****/
void Map::CreateMap()
{
	/****	�}�b�v�T�C�Y����	****/
	m_TileColumnList.resize(m_Mapdata.GetSize().x);

	/****	�u���b�N���Ǎ�	****/
	Vector2 Pos;

	int MapWidth = m_Mapdata.GetSize().x;
	int MapHeight = m_Mapdata.GetSize().y;
	vector<vector<char>> MapChip = *m_Mapdata.GetMapData();
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			/*	���W�ݒ�	*/
			float PosX = TILE_WIDTH * x;
			float PosY = TILE_HEIGHT * y;
			Pos.Set(PosX, PosY);

			/*	�u���b�N����	*/
			switch (MapChip[y][x])
			{
			case NB:
				CreateTile(Pos, "wh2", MAPOBJ::NB);
				break;

			case C1:
				CreateTile(Pos, "red3", MAPOBJ::C1);

				break;

			case C2:
				CreateTile(Pos, "bu", MAPOBJ::C2);
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}



}

/****	�^�C������	****/
void Map::CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj)
{

	int Column = (int)(in_Position.x / TILE_WIDTH);	//��

	m_TileColumnList[Column].Add(new Tile);				//��Ƀ^�C����ǉ�
	m_TileColumnList[Column].SetPosition(in_Position);	//���W�ݒ�
	m_TileColumnList[Column].SetSprite(FileName);		//�X�v���C�g�ݒ�
	m_TileColumnList[Column].SetKind(in_MapObj);		//��ސݒ�
	m_TileColumnList[Column].SetColumn((float)Column);	//��ݒ�
	m_TileColumnList[Column].mp_Column.back()->Start();	//������
															/*	�^�C�����X�g�ɕۑ�	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_Column.back());

}

/****	�I�u�W�F�N�g�ړ�����	****/
bool Map::MoveTile()
{
	if (m_isReturnMove == true)
	{

		if (m_SaveMoveColumnList.empty() == true)
		{
			//�Ō�̗񂪊���W�ɍs�����Ƃ��ɏI������
			MoveSwicthOFF();
			return true;
		}
		/*	�ړ������ɖ߂�	*/
		ReturnMoveColumn();
	}

	/*	�ړ������I��	*/
	if (m_MoveFrontColumnList.empty() == true && m_MoveBackColumnList.empty() == true)
	{
		//�Ō�̗񂪊���W�ɍs�����Ƃ��ɏI������
		MoveSwicthOFF();
		return true;
	}

	MoveFrontColumn();	//�O��ړ�
	MoveBackColumn();	//���ړ�

	return true;
}

/****	�ړ��O����ݒ�	****/
void Map::SetMoveFrontColumn(Tile& in_StandardTile)
{
	vector<int> MoveColumunNum;						//�ړ���z��
	vector<float> MoveVal;							//�ړ��x�N�g���z��
	MAPOBJ SearchObj = in_StandardTile.GetKind();	//�T���I�u�W�F�N�g
	/*	�X�^�[�g�T����	*/
	int SearchColumn = (int)in_StandardTile.GetMyColumn() + 1;

	/*	�T������	*/
	while (m_TileColumnList[SearchColumn].SearchStandardTile(SearchObj) == true)
	{
		MoveColumunNum.push_back(SearchColumn);	//�ړ���i�[

		/*	�ړ��ʊi�[	*/
		//�ړ��ʌv�Z����F �ړ��� = �ڕW�^�C�����WY - ��^�C�����WY
		float StandardPosY = m_TileColumnList[SearchColumn].GetStandardTile()->transform->Position.y;

		float Val = in_StandardTile.transform->Position.y - StandardPosY;
		MoveVal.push_back(Val);

		SearchColumn++;		//�m�F���i�߂�
	}

	/****	�ړ�����ݒ�	****/
	for (auto Now : MoveColumunNum)
	{
		MoveColumnInfo Info;
		Info.SetMoveColumun(&m_TileColumnList[Now]);

		/*	��^�C���ݒ�	*/
		Info.SetStandardTile(m_TileColumnList[Now].GetStandardTile());

		/*	�ړ��X�s�[�h	*/
		float Speed = MoveVal.front() / m_MoveTime;	//�X�s�[�h = �ړ��� / �ړ�����
		Info.SetSpeed(Speed);

		/*	�ړ��ʑ��	*/
		Info.SetMoveValue(MoveVal.front());

		/*	���~����	*/
		if (MoveVal.front() > 0)
		{
			//���~�̏ꍇm_isUp��false�ɂ���
			Info.m_isUp = false;
		}
		MoveVal.erase(MoveVal.begin());

		/*	���i�[	*/
		m_MoveFrontColumnList.push_back(Info);

	}

	/*	�ړ���ۑ�	*/
	copy(m_MoveFrontColumnList.begin(), m_MoveFrontColumnList.end(), back_inserter(m_SaveMoveColumnList));

	/*	�������	*/
	MoveColumunNum.clear();
	MoveVal.clear();
}

/****	�ړ������ݒ�	****/
void Map::SetMoveBackColumn(Tile& in_StandardTile)
{
	vector<int> MoveColumunNum;						//�ړ���z��
	vector<float> MoveVal;							//�ړ��x�N�g���z��
	MAPOBJ SearchObj = in_StandardTile.GetKind();	//�T���I�u�W�F�N�g
	/*	�X�^�[�g�T����	*/
	int SearchColumn = (int)in_StandardTile.GetMyColumn() - 1;

	/*	�T������	*/
	while (m_TileColumnList[SearchColumn].SearchStandardTile(SearchObj) == true)
	{
		MoveColumunNum.push_back(SearchColumn);	//�ړ���i�[

		/*	�ړ��ʊi�[	*/
		//�ړ��ʌv�Z����F �ړ��� = �ڕW�^�C�����WY - ��^�C�����WY
		float StandardPosY = m_TileColumnList[SearchColumn].GetStandardTile()->transform->Position.y;

		float Val = in_StandardTile.transform->Position.y - StandardPosY;
		MoveVal.push_back(Val);

		SearchColumn--;		//�m�F���i�߂�
	}

	/****	�ړ�����ݒ�	****/
	for (auto Now : MoveColumunNum)
	{
		MoveColumnInfo Info;
		Info.SetMoveColumun(&m_TileColumnList[Now]);

		/*	��^�C���ݒ�	*/
		Info.SetStandardTile(m_TileColumnList[Now].GetStandardTile());
		/*	�ړ��X�s�[�h	*/
		float Speed = MoveVal.front() / m_MoveTime;	//�X�s�[�h = �ړ��� / �ړ�����
		Info.SetSpeed(Speed);

		/*	�ړ��ʑ��	*/
		Info.SetMoveValue(MoveVal.front());

		/*	���~����	*/
		if (MoveVal.front() > 0)
		{
			//���~�̏ꍇm_isUp��false�ɂ���
			Info.m_isUp = false;
		}
		MoveVal.erase(MoveVal.begin());

		/*	���i�[	*/
		m_MoveBackColumnList.push_back(Info);

	}

	/*	�ړ���ۑ�	*/
	copy(m_MoveBackColumnList.begin(), m_MoveBackColumnList.end(), back_inserter(m_SaveMoveColumnList));

	/*	�������	*/
	MoveColumunNum.clear();
	MoveVal.clear();
}

/****	�ړ��ʕۑ��ݒ�	****/
bool Map::SetSaveColumn()
{

	int num = 0;

	/*	�ۑ��ړ��ݒ�	*/
	for (auto Now : m_SaveMoveColumnList)
	{
		/*	�ړ��ʑ��	*/
		float ReturnMoveValue = Now.ResetMoveValue();
		cout << "���Z�b�g���ړ���:" << ReturnMoveValue << endl;
		m_SaveMoveColumnList[num].SetMoveValue(ReturnMoveValue);

		/*	�ړ��X�s�[�h	*/
		float Speed = ReturnMoveValue / m_MoveTime;
		m_SaveMoveColumnList[num].SetSpeed(Speed);

		/*	�ړ��������]	*/
		m_SaveMoveColumnList[num].m_isUp = !Now.m_isUp;

		num++;

	}

	return true;
}

/****	�O��ړ�	****/
bool Map::MoveFrontColumn()
{

	if (m_MoveFrontColumnList.empty() == true)
	{
		cout << "�O��ړ��I��" << endl;
		return false;
	}
	m_MoveFrontColumnList.front().Move();
	/*	�ړ���폜	*/
	//�ڕW���W�ɒB������폜����
	if (m_MoveFrontColumnList.front().m_MoveValue == m_MoveFrontColumnList.front().m_NowMoveValue)
	{
		m_MoveFrontColumnList.erase(m_MoveFrontColumnList.begin());
	}


	return true;

}

/****	���ړ�	****/
bool Map::MoveBackColumn()
{

	if (m_MoveBackColumnList.empty() == true)
	{
		//Log::LogError("���vector�R���e�i���폜���Ă��܂�");
		cout << "���ړ��I��" << endl;
		return false;
	}
	m_MoveBackColumnList.front().Move();
	/*	�ړ���폜	*/
	//�ڕW���W�ɒB������폜����
	if (m_MoveBackColumnList.front().m_MoveValue == m_MoveBackColumnList.front().m_NowMoveValue)
	{
		m_MoveBackColumnList.erase(m_MoveBackColumnList.begin());
	}
	return true;
}


/****	��ړ��߂�	****/
bool Map::ReturnMoveColumn()
{
	int num = 0;
	/*	���Z�b�g�I��	*/
	if (m_SaveMoveColumnList.empty() == true)
	{
		m_isReturnMove = false;
		cout << "���Z�b�g�I��" << endl;
		return true;
	}

	//�����Ƀo�O����I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I�I
	//���͘A���Ō��ɖ߂������������Ă���
	//����͈�C�ɖ߂������ɕύX����
	m_SaveMoveColumnList.front().Move();
	/*	�ړ���폜	*/
	//�ڕW���W�ɒB������폜����
	if (m_SaveMoveColumnList.front().m_MoveValue == m_SaveMoveColumnList.front().m_NowMoveValue)
	{
		m_SaveMoveColumnList.erase(m_SaveMoveColumnList.begin());
	}	return true;
}


/****	�ړ��񃊃Z�b�g	****/
void Map::ResetColumnPos(vector<MoveColumnInfo>* out_ResetColumn)
{
	vector<float> ResetPositionY;
	for (auto NowColumn : *out_ResetColumn)
	{
		//ResetPositionY.push_back()
	}

}