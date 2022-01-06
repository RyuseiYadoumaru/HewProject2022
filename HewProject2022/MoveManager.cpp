#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"


/****	�R���X�g���N�^	****/
MoveManager::MoveManager()
{
	m_MoveWaitTime = 0.0f;
	m_Timer = 0.0f;
}

/****	������	****/
bool MoveManager::Init(vector<TileColumn>* in_AllTile, LandTile* in_StandardTile)
{
	//�ړ�����u���b�N������Ƃ���true�ŕԂ�

	/*	��^�C���ݒ�	*/
	m_StandardTile = in_StandardTile;

	/*	�J���[�u���b�N�ɏ�����Ƃ�	*/
	if (m_StandardTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		//�ړ��z��Ɋi�[
		bool ret = SetMoveList(in_AllTile);

		//�ړ��񂪂���Ƃ�
		if (ret == true)
		{
			//�ړ���̐��ɉ����đҋ@���Ԃ�ς���
			m_MoveWaitTime = (Front.Num() * m_OneColumnWaitTime) + (Back.Num() * m_OneColumnWaitTime);
			//�^�C�}�[������
			m_Timer = 0.0f;
			return true;
		}
	}

	return false;
}

/****	�X�V	****/
bool MoveManager::Update()
{
	bool isFin = false;
	/****	�ړ�����	****/
	if (Front.Empty() == false ||
		Back.Empty() == false)
	{
		//�ړ����X�g���󂶂�Ȃ��Ƃ�

		if (m_Timer >= m_MoveWaitTime)
		{
			//�ҋ@���ԕ��܂�
			isFin = Move();
		}
		else
		{
			//���ԍX�V
			m_Timer += GameTimer::deltaTime();
		}

	}
	else
	{
		m_Timer = 0.0f;
		isFin = true;
	}

	//�I���̎���true��Ԃ�
	return isFin;
}

/****	����Ă�I�u�W�F�N�g�̖��O�擾	****/
string & MoveManager::GetLandObjectName()
{
	return m_StandardTile->GetOwnerName();
}

/****	����Ă���I�u�W�F�N�g��ID�擾����	****/
int MoveManager::GetLandObjectID() const
{
	return (int)m_StandardTile->GetOwnerID();
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------

/****	�ړ����X�g�쐬	****/
bool MoveManager::SetMoveList(vector<TileColumn>* in_AllTile)
{
	//�ړ��񂪂���Ƃ���true��Ԃ�

	/****	���ݒ�	****/
	int NowColumn = m_StandardTile->GetLandTile()->GetMyColumn();
	//����Ă��̊������Ă���
	in_AllTile->at(NowColumn).m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());

	/****	�O�T��	****/
	/*	�X�^�[�g�T����	*/
	int SearchColumn = NowColumn + 1;

	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		/*	���݂̃|�W�V�����ƈႤ�ꏊ�Ɉړ�����Ƃ�	*/
		if (in_AllTile->at(SearchColumn).m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Front.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());

		}
		//�T����X�V
		SearchColumn++;
	}

	/****	��T��	****/
	/*	�X�^�[�g�T����	*/
	SearchColumn = NowColumn - 1;
	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		if (in_AllTile->at(SearchColumn).m_MoveInfo->GetPositionEqual() == false)
		{
			//�ړ���i�[
			Back.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		}
		//�T����X�V
		SearchColumn--;
	}

	//�O�����Ɉړ��񂪂���Ƃ���true��Ԃ�
	if (Back.Empty() == false || Front.Empty() == false) return true;

	//�����Ȃ�����false��Ԃ�
	return false;

}

/****	�ړ�����	****/
bool MoveManager::Move()
{
	/*	�I���t���O	*/
	bool isFrontFin = false;
	bool isBackFin = false;

	/*	�O�ړ�	*/
	if (Front.Empty() == false)
	{
		/*	��ړ�����	*/
		Front.MoveFront();
	}

	/*	�ړ��񂪂Ȃ��Ȃ�����	*/
	if (Front.Empty() == true)
	{
		//�I��flag�𗧂ĂĂ���
		isFrontFin = true;
	}

	/*	��ړ�	*/
	if (Back.Empty() == false)
	{
		Back.MoveFront();
	}

	/*	�ړ��񂪂Ȃ��Ȃ�����	*/
	if (Back.Empty() == true)
	{
		//�I��flag�𗧂ĂĂ���
		isBackFin = true;
	}

	//�I���̎���true��Ԃ�
	if (isFrontFin == true && isBackFin == true)
	{
		return true;
	}

	return false;

}