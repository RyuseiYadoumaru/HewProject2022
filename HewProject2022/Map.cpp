#include "Map.h"
#include "Engine/Create/Scene.h"
using Math::Vector3;

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
vector<shared_ptr<MoveManager>> Map::m_MoveManager;		//�ړ�
vector<TileColumn>				Map::m_TileColumnList;	//1��^�C�����X�g
vector<Tile*>					Map::m_TileList;		//�S�Ẵ^�C�����X�g
bool							Map::m_OnReset = false;	//���Z�b�g�t���O
bool							Map::m_isResetStart = false;

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

/****	�S�Ẵ^�C�������Z�b�g����	****/
void Map::AllTileReset()
{
	for (auto& Column : m_TileColumnList)
	{
		if (Column.mp_TileList.empty() == false)
		{

			for (auto& tile : Column.mp_TileList)
			{
				tile->transform->Position.y = tile->GetStartPosition().y;
				if (BlockParticleManager::DeleteMoveEffect(tile->GetId().x) == true)
				{
					if (BlockParticleManager::JudgeRedorBlue(tile->GetKind()) == EFFECT_RED)
					{
						BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::RED);
					}
					else
					{
						BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::BLUE);
					}
				}
			}
		}
	}

	/*	���Z�b�gSE�Đ�	*/
	Sound::Sound_Play(SOUND_LABEL_RESETBLOCK);//���n���ʉ��Đ�

}

//-----------------------------------------------------------------------------
// Public Function
//-----------------------------------------------------------------------------
/****	�R���X�g���N�^	****/
Map::Map()
{
	m_MapDataName = "ProtMap";
	m_OnReset = false;	//���Z�b�g�t���O
	m_isResetStart = false;
}

Map::Map(std::string in_MapDataName) : GameObject(in_MapDataName)
{
	m_MapDataName = in_MapDataName;
	m_OnReset = false;	//���Z�b�g�t���O
	m_isResetStart = false;
}

/****	������	****/
bool Map::Start()
{
	/*	�}�b�v������	*/
	transform->Position.Set(3640.0f, 840.0f, 0.0f);

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
	/*	��X�V	*/
	ColumnUpdate();

	/*	��ړ��̍X�V	*/
	MoveUpdate();

	/*	�񃊃Z�b�g����	*/
	if (m_OnReset == true)
	{
		MoveReset();
	}
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

	/*	�p�[�e�B�N�����	*/
	m_MoveParticle.End();
	return true;
}

/****	�`��	****/
bool Map::Render()
{
	Create::Camera* camera = Create::Scene::GetCamera();
	/****	�^�C���`��	****/
	for (auto& now : m_TileList)
	{
		if (now->transform->Position.x >= camera->GetLeft() - 80.0f&& now->transform->Position.x <= camera->GetRight() + 80.0f &&
			now->transform->Position.y >= camera->GetTop() - 80.0f && now->transform->Position.y <= camera->GetButtom() + 80.0f)
		{
			now->Render();
		}
	}

	/****	�p�[�e�B�N���`��	****/
	m_MoveParticle.ParticleRender();

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
	for (auto& i : m_TileList)
	{
		for (auto& system : i->ComponentList)
		{
			system->Update();
		}
	}
}

/****	�}�b�v�����蔻��	****/
bool Map::HitCheckMap(GameObject& in_GameObject, CHECK in_Check)
{
	int debug = 0;

	/*	�q�b�g�`�F�b�N�I�u�W�F�N�g	*/
	BoxCollider2D* CheckObject = in_GameObject.GetComponent<BoxCollider2D>();
	Create::Camera* camera = Create::Scene::GetCamera();

	/*	�����蔻��	*/

	//�J�����͈͊O���`�F�b�N����
	if (in_Check == ALL)
	{
		for (auto& NowTile : m_TileList)
		{
			BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
			debug++;
			CheckObject->HitCheckBox(*TileCol);
		}
	}

	//�J�����͈͓��`�F�b�N
	else if (in_Check == CAMERA_RANGE)
	{
		for (auto& NowTile : m_TileList)
		{
			if (NowTile->transform->Position.x >= camera->GetLeft() && NowTile->transform->Position.x <= camera->GetRight() &&
				NowTile->transform->Position.y >= camera->GetTop() && NowTile->transform->Position.y <= camera->GetButtom())
			{
				debug++;

				BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
				if (NowTile->tag != TagList::STAR) {
					CheckObject->HitCheckBox(*TileCol);
				}
			}
		}
	}

	else if (in_Check == CAMERA_OBHECT_RANGE)
	{
		/*	�����ɏk�������␳�l���v�Z����	*/
		//////////////////////////////////////////
		/////////////////////////////////////////
		////////////////////////////////////////
		///////////////////////////////////////
		for (auto& NowTile : m_TileList)
		{
			if (NowTile->transform->Position.x >= camera->GetLeft() && NowTile->transform->Position.x <= camera->GetRight() &&
				NowTile->transform->Position.y >= camera->GetTop() && NowTile->transform->Position.y <= camera->GetButtom())
			{
				debug++;

				BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
				if (NowTile->tag != TagList::STAR) {
					CheckObject->HitCheckBox(*TileCol);
				}
			}
		}
	}

	else if (in_Check == OBJECT_RANGE)
	{

		/*	�R���C�_�͈̔͂̂݃`�F�b�N����	*/
		float left = CheckObject->GetCenterPos().x - (CheckObject->GetCenterLength().x + 100.0f);
		float right = CheckObject->GetCenterPos().x + (CheckObject->GetCenterLength().x + 100.0f);
		float top = CheckObject->GetCenterPos().y - (CheckObject->GetCenterLength().y + 100.0f);
		float buttom = CheckObject->GetCenterPos().y + (CheckObject->GetCenterLength().y + 100.0f);


		/*	�����蔻��	*/
		for (auto& NowTile : m_TileList)
		{
			if (NowTile->transform->Position.x >= left && NowTile->transform->Position.x <= right &&
				NowTile->transform->Position.y >= top && NowTile->transform->Position.y <= buttom)
			{
				debug++;

				BoxCollider2D* TileCol = NowTile->GetComponent<BoxCollider2D>();
				if (NowTile->tag != TagList::STAR) {
					CheckObject->HitCheckBox(*TileCol);
				}
			}
		}
	}


	cout << "�����蔻��̎Q�Ɖ񐔁F" << debug << endl;
	return true;
}

/****	�`�F�b�N�^�C���ۑ�	****/
bool Map::CheckLandTile(LandTile& in_LandTile)
{
	/*	�^�C�����ς���ĂȂ��Ƃ�	*/
	//�^�C�����ς���Ă��Ȃ�
	//����Ă���^�C������������ɑ����u���b�N�̎�
	if (in_LandTile.GetisChange() == false ||
		in_LandTile.GetLandTile()->tag != TagList::LandColorBlock)
	{
		//�ۑ����Ȃ�
		return true;
	}

	/*	�`�F�b�N	*/
	if (in_LandTile.GetSaveLandTile() == nullptr)
	{
		//�f�t�H���g1���ڂ̃^�C���ɏ������
		/*	�ړ��}�l�[�W���[�ǉ�	*/
		AddMoveManager(&in_LandTile);
		return true;


	}

	if (in_LandTile.GetLandTile()->tag == TagList::LandColorBlock && in_LandTile.GetSaveLandTile()->tag != TagList::ColorBlock)
	{
		if (in_LandTile.GetLandTile()->GetKind() == in_LandTile.GetSaveLandTile()->GetKind() &&
			in_LandTile.GetLandTile()->transform->Position.y == in_LandTile.GetSaveLandTile()->transform->Position.y)
		{
			//������ނ̃I�u�W�F�N�g����Y���W�������Ƃ���
			//�������Ƃ��Ȃ��̂ŒT�����Ȃ�
			return true;
		}
	}

	/*	�ړ��}�l�[�W���[�ǉ�	*/
	AddMoveManager(&in_LandTile);

	return true;
}

void Map::MoveReset()
{
	/*	���Z�b�g�����s�\	*/
	if (m_isReset == false)
	{
		cout << "���Z�b�g���Ȃ�\n";
		//true�̎��Ƀu���b�N���ړ����Ă���̂Ń��Z�b�g���邱�Ƃ��ł���
		m_OnReset = false;
		m_isResetStart = false;
		m_isReset = false;
		return;
	}
	cout << "�񃊃Z�b�g\n";


	//���ڂ̎��͏��������s��
	if (m_isResetStart == false)
	{
		/*	���Z�b�g������	*/
		m_isResetStart = true;
		bool ret = m_ResetManager.Init();
		cout << "���Z�b�g����������\n";
		/*	���Z�b�g����	*/
		if (ret == false)
		{
			cout << "���Z�b�g��Ȃ�\n";
			m_isReset = false;
			m_OnReset = false;
			m_isResetStart = false;

			return;
		}
	}

	/*	���Z�b�g�X�V����	*/
	m_isReset = m_ResetManager.Update();

}


/****	�񏉊���	****/
void Map::ColumnInit()
{
	/*****	���W�ݒ�	****/
	//�}�b�v�̒��S����ɂ���
	Vector3 SetPosition;
	float MapWidth = m_Mapdata.GetSize().x;
	float MapHeight = m_Mapdata.GetSize().y;
	SetPosition.x = transform->Position.x - ((MapWidth / 2.0f) * TILE_WIDTH);
	SetPosition.y = transform->Position.y - ((MapHeight / 2.0f) * TILE_HEIGHT);

	//�S�Ẵu���b�N�ɑ��
	for (auto& tile : m_TileList)
	{
		tile->transform->Position += SetPosition;
	}
	/*	������	*/
	for (auto& Column : m_TileColumnList)
	{
		Column.Init();
	}

}

/****	��X�V	****/
void Map::ColumnUpdate()
{
	for (auto& Column : m_TileColumnList)
	{
		Column.Update();
	}

}

/****	�}�b�v��������	****/
void Map::CreateMap()
{
	/****	�}�b�v�T�C�Y����	****/
	m_TileColumnList.resize((UINT)m_Mapdata.GetSize().x);

	/****	�u���b�N���Ǎ�	****/
	Vector2 Pos;

	float MapWidth = m_Mapdata.GetSize().x;
	float MapHeight = m_Mapdata.GetSize().y;

	vector<vector<char>> MapChip = *m_Mapdata.GetMapData();
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			/*	���W�ݒ�	*/
			float PosX = TILE_WIDTH * x;
			float PosY = (TILE_HEIGHT * y);

			Pos.Set(PosX, PosY);

			/*	�u���b�N����	*/
			switch (MapChip[y][x])
			{
			case NB:
				CreateNormalBlock(Pos);
				//CreateTile(Pos, "brown1", MAPOBJ::NB);
				break;

			case C1:
				CreateTile(Pos, "red", MAPOBJ::C1);
				break;

			case C2:
				CreateTile(Pos, "blue", MAPOBJ::C2);
				break;

			case C3:
				CreateTile(Pos, "green", MAPOBJ::C3);
				break;

			case C4:
				CreateTile(Pos, "purple", MAPOBJ::C4);
				break;
				//3�F�ω��^�C��
			case CR3:
				CreateChangeTile(Pos, "red_blue", MAPOBJ::CR3);
				break;

			case CB3:
				CreateChangeTile(Pos, "blue_green", MAPOBJ::CB3);
				break;

			case CG3:
				CreateChangeTile(Pos, "green_red", MAPOBJ::CG3);
				break;

				//4�F�ω��^�C��
			case CR4:
				CreateChangeTile(Pos, "red_blue", MAPOBJ::CR4);
				break;

			case CB4:
				CreateChangeTile(Pos, "blue_green", MAPOBJ::CB4);
				break;

			case CG4:
				CreateChangeTile(Pos, "green_purple", MAPOBJ::CG4);
				break;

			case CP4:
				CreateChangeTile(Pos, "purple_red", MAPOBJ::CP4);
				break;

				//�����h�u���b�N
			case LC1:
				CreateTile(Pos, "Landred", MAPOBJ::LC1);
				break;

			case LC2:
				CreateTile(Pos, "Landblue", MAPOBJ::LC2);
				break;
			case LC3:
				CreateTile(Pos, "Landgreen", MAPOBJ::LC3);
				break;
			case LC4:
				CreateTile(Pos, "Landpurple", MAPOBJ::LC4);
				break;

			case ST:
				CreateStarTile(Pos, "hosi", MAPOBJ::ST);
				break;
			case GR:
				break;

			case NO:
				break;

			default:
				break;
			}
		}
	}
}

/****	�m�[�}���u���b�N����	****/
void Map::CreateNormalBlock(Vector2& in_Pos)
{
	//�m�[�}���u���b�N�͗����ŗl�X�Ȏ�ނ𐶐�����
	SystemTimer* timer = SystemTimer::Instance();
	int randTime = (int)timer->GetSystemCurrentTime();
	int num = (randTime + (int)rand() + (int)rand()) % 3 + 1;
	if (num == 1)
	{
		CreateTile(in_Pos, "brown1", MAPOBJ::NB);
	}
	else if (num == 2)
	{
		CreateTile(in_Pos, "brown2", MAPOBJ::NB);

	}
	else if (num == 3)
	{
		CreateTile(in_Pos, "brown3", MAPOBJ::NB);

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

		/*	�^�C�����X�g�ɕۑ�	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_TileList.back());

}

/****	����ւ��^�C������	****/
void Map::CreateChangeTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj)
{

	int Column = (int)(in_Position.x / TILE_WIDTH);	//��

	m_TileColumnList[Column].Add(new ChangeTile);				//��Ƀ^�C����ǉ�
	m_TileColumnList[Column].SetPosition(in_Position);	//���W�ݒ�
	m_TileColumnList[Column].SetSprite(FileName);		//�X�v���C�g�ݒ�
	m_TileColumnList[Column].SetKind(in_MapObj);		//��ސݒ�
	m_TileColumnList[Column].SetColumn((float)Column);	//��ݒ�

		/*	�^�C�����X�g�ɕۑ�	*/
	m_TileList.push_back(m_TileColumnList[Column].mp_TileList.back());

}

void Map::CreateStarTile(Vector2 & in_Position, string FileName, MAPOBJ in_MapObj)
{
	int Column = (int)(in_Position.x / TILE_WIDTH);	//��


	m_TileColumnList[Column].Add(new StarTile);				//��ɐ���ǉ�
	NAME n = "Star" + std::to_string(m_TileColumnList[Column].mp_TileList.back()->GetId().x);
	m_TileColumnList[Column].mp_TileList.back()->SetName(n);
	m_TileColumnList[Column].SetPosition(in_Position);	//���W�ݒ�
	m_TileColumnList[Column].SetSprite(FileName);		//�X�v���C�g�ݒ�
	m_TileColumnList[Column].SetKind(in_MapObj);		//��ސݒ�
	m_TileColumnList[Column].SetColumn((float)Column);	//��ݒ�

		//m_TileColumnList[Column].mp_TileList.back()->Start();	//������

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
			//�ړ��������������߃��Z�b�g�t���O�𗧂Ă�
			m_isReset = true;	//true�̎��Ƀ��Z�b�g�\
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
	if (m_MoveManager.back()->Init(in_LandTile) == false)
	{
		//�ړ��񂪖���������������
		m_MoveManager.back().reset();
		m_MoveManager.back() == nullptr;
		m_MoveManager.pop_back();

	}
}