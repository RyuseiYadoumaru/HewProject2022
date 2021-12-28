#include "Map.h"
#include "Engine/Create/Scene.h"
using Math::Vector3;

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
vector<shared_ptr<MoveManager>> Map::m_MoveManager;		//�ړ���
vector<TileColumn>				Map::m_TileColumnList;	//1��^�C�����X�g
vector<Tile*>					Map::m_TileList;		//�S�Ẵ^�C�����X�g

/****	�����Ă���I�u�W�F�N�g�T��	****/
bool Map::SearchMoveObjectName(string in_SearchName)
{
	/*	�ړ����X�g�̒��g������Ƃ�	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	�ړ����X�g�I�u�W�F�N�g�`�F�b�N	*/
			if (NowMove->GetLandObjectName() == in_SearchName)
			{
				cout << NowMove->GetLandObjectName() << "���K�`���Ă܂�\n";
				//�T���I�u�W�F�N�g����
				return true;
			}
		}
	}

	//�T���I�u�W�F�N�g�Ȃ�
	return false;
}

/****	�����Ă���I�u�W�F�N�g�T��	****/
bool Map::SearchMoveObjectID(int in_ID)
{
	/*	�ړ����X�g�̒��g������Ƃ�	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	�ړ����X�g�I�u�W�F�N�g�`�F�b�N	*/
			if (NowMove->GetLandObjectID() == in_ID)
			{
				cout << NowMove->GetLandObjectName() << "���K�`���Ă܂�\n";
				//�T���I�u�W�F�N�g����
				return true;
			}
		}
	}

	//�T���I�u�W�F�N�g�Ȃ�
	return false;
}

//-----------------------------------------------------------------------------
// Public Function
//-----------------------------------------------------------------------------
/****	�R���X�g���N�^	****/
Map::Map()
{
	m_MapDataName = "ProtMap";
}

Map::Map(std::string in_MapDataName) : GameObject(in_MapDataName)
{
	m_MapDataName = in_MapDataName;

}

/****	������	****/
bool Map::Start()
{
	/*	�}�b�v���[�h	*/
	m_Mapdata.Load(m_MapDataName);

	/*	�}�b�v����	*/
	CreateMap();

	/*	�񏉊���	*/
	ColumnInit();
	return true;
}

/****	�X�V	****/
bool Map::Update()
{

	/*	��ړ��̍X�V	*/
	MoveUpdate();

	/*	��X�V	*/
	ColumnUpdate();

	//�O�،��ǉ�
	//�񃊃Z�b�g
	MoveReset();

	return true;
}

/****	�I������	****/
bool Map::End()
{
	/*	�^�C�����X�g�I������	*/
	m_TileList.clear();

	for (auto& List : m_TileColumnList)
	{
		List.End();
	}
	m_TileColumnList.clear();

	/*	�ړ��}�l�[�W���[���	*/
	for (auto& MoveInfo : m_MoveManager)
	{
		MoveInfo.reset();
	}
	m_MoveManager.clear();
	return true;
}

/****	�`��	****/
bool Map::Render()
{
	Create::Camera* camera = Create::Scene::GetCamera();
	for (int Column = 0; Column < m_Mapdata.GetSize().x; Column++)
	{
		for (auto now : m_TileColumnList[Column].mp_TileList)
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

/****	�f�o�b�O����	****/
void Map::Debug()
{
	/*	�^�C���f�o�b�O	*/
	for (auto List : m_TileColumnList)
	{
		List.Debug();
	}
}


/****	�V�X�e���A�b�v�f�[�g	****/
void Map::SystemUpdate()
{
	//�R���|�[�l���g�V�X�e���X�V
	for (auto i : m_TileList)
	{
		for (auto system : i->ComponentList)
		{
			system->Update();
		}
	}
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
		for (auto NowTile : Search.mp_TileList)
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

/****	�`�F�b�N�^�C���ۑ�	****/
bool Map::CheckLandTile(LandTile* in_LandTile)
{
	/*	�^�C�����ς���ĂȂ��Ƃ�	*/
	if (in_LandTile->GetisChange() == false)
	{
		//�ۑ����Ȃ�
		return true;
	}
	/*	�`�F�b�N	*/
	if (in_LandTile->GetLandTile()->GetKind() == in_LandTile->GetSaveLandTile()->GetKind() &&
		in_LandTile->GetLandTile()->transform->Position.y == in_LandTile->GetSaveLandTile()->transform->Position.y)
	{
		//������ނ̃I�u�W�F�N�g����Y���W�������Ƃ���
		//�������Ƃ��Ȃ��̂ŒT�����Ȃ�
		return true;
	}
	/*	�ړ��}�l�[�W���[�ǉ�	*/
	AddMoveManager(in_LandTile);

	return true;
}


/****	�񏉊���	****/
void Map::ColumnInit()
{
	for (auto& Column : m_TileColumnList)
	{
		Column.Init();
		//Column.m_MoveInfo.SetColumn(&Column);
	}
}

/****	��X�V	****/
void Map::ColumnUpdate()
{
	for (auto Column : m_TileColumnList)
	{
		Column.Update();
	}
}

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

			case C3:
				CreateTile(Pos, "gr", MAPOBJ::C3);
				break;

			case GR:
				CreateTile(Pos, "NormalBlock", MAPOBJ::GR);
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
	m_TileColumnList[Column].mp_TileList.back()->Start();	//������

	/*	�^�C�����X�g�ɕۑ�	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_TileList.back());

}

/****	�ړ��X�V	****/
void Map::MoveUpdate()
{
	//�z��̒��g������Ƃ��̍X�V��������
	if (m_MoveManager.empty() == false)
	{
		//�z��̐擪����X�V��������
		bool ret = m_MoveManager.front()->Update();
		if (ret == true)
		{
			//�ړ����I�������������
			m_MoveManager.front().reset();
			m_MoveManager.front() = nullptr;
			m_MoveManager.erase(m_MoveManager.begin());
		}
	}
}

/****	�ړ��}�l�[�W���[�ǉ�	****/
void Map::AddMoveManager(LandTile* in_LandTile)
{

	/*	�ړ����X�g�̒��g������Ƃ�	*/
	if (m_MoveManager.empty() == false)
	{
		for (auto& NowMove : m_MoveManager)
		{
			/*	�ړ����X�g�I�u�W�F�N�g�`�F�b�N	*/
			if (NowMove->GetLandObjectID() == in_LandTile->GetOwnerID())
			{
				//���X�g�ɓ����I�u�W�F�N�g������Εۑ����Ȃ�
				cout << "�����I�u�W�F�N�g���ړ����X�g�ɂ���܂����I\n";
				return;
			}
		}
	}

	/*	�^�C���ۑ�	*/
	cout << "�^�C���ۑ�\n";
	m_MoveManager.push_back(make_shared<MoveManager>());	//�ҋ@��Ɉړ��������
	/*	�ړ���񏉊�������	*/
	if (m_MoveManager.back()->Init(&m_TileColumnList, in_LandTile) == false)
	{
		//�ړ��񂪖���������������
		m_MoveManager.back().reset();
		m_MoveManager.back() == nullptr;
		m_MoveManager.pop_back();

	}
}

void Map::MoveReset()
{
	SystemTimer* Timer = SystemTimer::Instance();

	if (Input::GetKeyTrigger(PK_3)) {

		for (int i = 0; i < m_TileList.size(); i++) {

			//�X�^�[�g���W�ɖ߂�܂œ���
			if (m_TileList[i]->transform->Position.y >= m_TileList[i]->GetStartPosition().y) {
				for (int j = 0; j < m_TileColumnList.size(); j++) {

					//�ړ��ʁE�ړ��X�s�[�h�v�Z
					m_ResetMoveValue = m_TileList[j]->GetStartPosition().y - m_TileList[j]->transform->Position.y;
					//m_ResetSpeed = m_ResetMoveValue / 0.8f;//�����̐����傫������ƁA��肭�������W�ɖ߂�Ȃ��i�����͕s���j
					m_ResetSpeed = m_ResetMoveValue / 100.5f;//�����̐����傫������ƁA��肭�������W�ɖ߂�Ȃ��i�����͕s���j
					m_ResetVectorY = m_ResetSpeed * Timer->DeltaTime();

					//�ړ�
					m_TileList[i]->transform->Position.y += m_ResetVectorY;
				}
			}
			//���艟��
			m_TileList[i]->transform->Position.y = m_TileList[i]->GetStartPosition().y;
		}
	}
}
