#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "Map.h"



/****	�R���X�g���N�^	****/
LandTile::LandTile(std::string in_name) : GameObject(in_name)
{
}

/****	������	****/
bool LandTile::Start()
{
	/*	�����h�^�C�������蔻��ݒ�	*/
	Vector2 size(20.0f, 20.0f);
	BoxCollider2D* col = AddComponent<BoxCollider2D>(size);
	col->SetOffset(offsetX, 3.75f);
	return true;
}

/****	������	****/
bool LandTile::Init(GameObject* in_Owner)
{

	isChange = false;

	/*	�I�[�i�[�擾	*/
	Owner = in_Owner;
	transform->Position = Owner->transform->Position;
	OwnerName = Owner->GetName();

	//����Ă���^�C��������
	LandTileInit();

	return true;
}

/****	�X�V	****/
bool LandTile::Update()
{
	/*	����Ă�^�C���𒲂ׂ�	*/
	transform->Position = Owner->transform->Position;

	/*	�}�b�v�����蔻��	*/
	Map::HitCheckMap(*this, Map::CHECK::CAMERA_RANGE);
	//�����ɓ����蔻��̏���������
	SearchLandingTile();

	/*	����Ă�^�C�����ς�������m�F����	*/
	isChange = true;
	if (mp_LandingTile == mp_SaveLandingTile)
	{
		isChange = false;
	}
	return true;
}


/****	�f�o�b�O	****/
void LandTile::Debug()
{
	GetComponent<BoxCollider2D>()->Debug(1.0f, 0.0f);
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	����Ă�^�C���𒲂ׂ�	****/
void LandTile::SearchLandingTile()
{
	/*	���݂̃^�C���m�F	*/

	BoxCollider2D* Col = GetComponent<BoxCollider2D>();
	//���n�����Ƃ��Ɋi�[����
	if (Col->GetisHit_underBlock() == false)
	{
		/*	�}�W�b�N����	*/
		if (mp_SaveLandingTile != LandGround) BlockParticleManager::MagicReset(*mp_SaveLandingTile);

		m_isLandTile = false;
		mp_LandingTile = LandGround;
		return;
	}
	/*	�O�t���[���̃^�C����ۑ�	*/
	mp_SaveLandingTile = mp_LandingTile;

	//�����蔻�肪���Ă���I�u�W�F�N�g��ID���i�[
	const vector<ID>& IdList = Col->GetHitObjectId();

	/*	�^�C���I�u�W�F�N�gID�T��	*/
	for (auto Id : IdList)
	{
		/*	�^�C��ID�̎�	*/
		if (Id > TILE_ID)
		{
			//�^�C���T��
			Tile* tmp = FindTile(Id);
			//�G���[�`�F�b�N
			if (tmp == nullptr)
			{
				return;
			}

			//����Ă�^�C���m��
			SetLandTile(tmp);
			m_isLandTile = true;
			//����Ă��i�[
			NowColumn = mp_LandingTile->GetMyColumn();
		}

		/*	���ʃI�u�W�F�N�g	*/
		else
		{
			//����Ă�^�C��������
			LandTileInit();
			//�T���I��
			break;
		}
	}

}

/****	�^�C���h�c�T��	****/
Tile* LandTile::FindTile(ID& in_Id)
{
	/*	�^�C���T��	*/
	for (auto& tile : Map::m_TileList)
	{	/*	ID�q�b�g	*/
		if (tile->GetId() == in_Id)
		{
			return tile;
		}
	}

	return nullptr;
}

/****	����Ă�^�C���m��	****/
void LandTile::SetLandTile(Tile* in_JudgeTile)
{
	//�I�[�i�[�̃R���C�_��艺�̎�
	BoxCollider2D* col = Owner->GetComponent<BoxCollider2D>();
	float ButtomPos = col->GetCenterPos().y + col->GetCenterLength().y;
	if (ButtomPos < in_JudgeTile->transform->Position.y)
	{
		//nullptr����Ȃ��Ƃ��͔�������
		if (mp_LandingTile != nullptr)
		{
			//�����蔻��̒��ň��X���W�̐�Βl���߂��^�C��
			float NowDistanceX = fabsf(Owner->transform->Position.x - mp_LandingTile->transform->Position.x);
			float JudgeDistanceX = fabsf(Owner->transform->Position.x - in_JudgeTile->transform->Position.x);

			//�����蔻��̒���1��X���W���v���C���[�Ƌ߂��^�C��
			if (NowDistanceX > JudgeDistanceX)
			{
				mp_LandingTile = in_JudgeTile;
			}
		}

		//nullptr�̎��͒��ڑ��
		else
		{
			mp_LandingTile = in_JudgeTile;
			mp_SaveLandingTile = nullptr;
		}

	}

}


/****	����Ă�^�C��������	****/
void LandTile::LandTileInit()
{
	m_isLandTile = false;
	mp_LandingTile = LandGround;
	mp_SaveLandingTile = mp_LandingTile;
	NowColumn = NULL;
}
