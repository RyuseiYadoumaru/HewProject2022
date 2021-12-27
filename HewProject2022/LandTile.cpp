#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"

/****	������	****/
bool LandTile::Init(GameObject* in_Owner, vector<TileColumn>* in_NowMap)
{
	/*	�G���[�`�F�b�N	*/
	if (in_NowMap == nullptr)
	{
		Log::LogError("�}�b�v��Null�ł��B");
		return false;

	}
	isChange = false;

	/*	�I�[�i�[�擾	*/
	Owner = in_Owner;
	OwnerName = Owner->GetName();

	//���݃}�b�v�̃A�h���X�ۑ�
	mp_NowMap = in_NowMap;

	//����Ă���^�C��������
	LandTileInit();


	return true;
}

/****	�X�V	****/
bool LandTile::Update()
{

	/*	����Ă�^�C���𒲂ׂ�	*/
	SearchLandingTile();

	/*	����Ă�^�C�����ς�������m�F����	*/
	isChange = true;
	if (mp_LandingTile == mp_SaveLandingTile)
	{
		isChange = false;
	}
	//else if (mp_SaveLandingTile == nullptr && mp_LandingTile != nullptr)
	//{
	//	mp_SaveLandingTile = mp_LandingTile;
	//}
	return true;
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------
/****	����Ă�^�C���𒲂ׂ�	****/
void LandTile::SearchLandingTile()
{
	/*	���݂̃^�C���m�F	*/
	BoxCollider2D* Col = Owner->GetComponent<BoxCollider2D>();
	//���n�����Ƃ��Ɋi�[����
	if (Col->GetisHit_underBlock() == false)
	{
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
				Log::LogError("�^�C��ID�T�������Ɏ��s");
				return;
			}

			//����Ă�^�C���m��
			SetLandTile(tmp);
			m_isLandTile = true;
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
	/*	��T��	*/
	for (auto Now : *mp_NowMap)
	{
		/*	�^�C���T��	*/
		for (auto tile : Now.mp_TileList)
		{
			/*	ID�q�b�g	*/
			if (tile->GetId() == in_Id)
			{
				return tile;
			}
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
	mp_LandingTile = nullptr;
	mp_SaveLandingTile = mp_LandingTile;
	NowColumn = NULL;
}
