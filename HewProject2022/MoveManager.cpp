#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"

/****	������	****/
bool MoveManager::Init(vector<TileColumn>* in_AllTile, LandTile* in_StandardTile)
{
	//�ړ�����u���b�N������Ƃ���true�ŕԂ�

	/*	��^�C���ݒ�	*/
	m_StandardTile = in_StandardTile;

	/*	�m�[�}���u���b�N�ɏ�����Ƃ�	*/
	if (m_StandardTile->GetLandTile()->tag == TagList::NormalBlock &&
		m_StandardTile->GetSaveLandTile()->tag == TagList::ColorBlock)
	{
		//	���Z�b�g�z��Ɋi�[����
		SetResetList(in_AllTile);

		return true;
	}

	/*	�J���[�u���b�N�ɏ�����Ƃ�	*/
	else if (m_StandardTile->GetLandTile()->tag == TagList::ColorBlock)
	{
		//�ړ��z��Ɋi�[
		SetMoveList(in_AllTile);
		return true;
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
		isFin = Move();

	}

	/****	���Z�b�g����	****/
	else if (Reset.Empty() == false)
	{
		//���Z�b�g�̒��g���󂶂�Ȃ��Ƃ�
		isFin = ResetMove();
	}

	else
	{
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
void MoveManager::SetMoveList(vector<TileColumn>* in_AllTile)
{
	/****	���ݒ�	****/
	int NowColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn();
	//����Ă��̊������Ă���
	in_AllTile->at(NowColumn).m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());

	/****	�O�T��	****/
	/*	�X�^�[�g�T����	*/
	int SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() + 1;

	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//�ړ���i�[
		Front.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//�T����X�V
		SearchColumn++;
	}

	/****	��T��	****/
	/*	�X�^�[�g�T����	*/
	SearchColumn = m_StandardTile->GetLandTile()->GetMyColumn() - 1;

	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//�ړ���i�[
		Back.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//�T����X�V
		SearchColumn--;
	}

}

/****	���Z�b�g���X�g�쐬	****/
void MoveManager::SetResetList(vector<TileColumn>* in_AllTile)
{

	/****	����Ă����ꏊ��ǉ�����	****/
	int NowColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn();
	Reset.Add(in_AllTile->at(NowColumn).m_MoveInfo.get());

	/****	�O�T��	****/
	/*	�X�^�[�g�T����	*/
	int SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() + 1;

	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchResetTile(m_StandardTile->GetSaveLandTile()))
	{
		//1�̏���Ă����^�C���ŒT������
		//�ړ���i�[
		Reset.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//�T����X�V
		SearchColumn++;
	}

	/****	��T��	****/
	/*	�X�^�[�g�T����	*/
	SearchColumn = m_StandardTile->GetSaveLandTile()->GetMyColumn() - 1;
	/*	�T������	*/
	while (in_AllTile->at(SearchColumn).m_MoveInfo->SearchResetTile(m_StandardTile->GetSaveLandTile()))
	{
		//1�̏���Ă����^�C���ŒT������
		//�ړ���i�[
		Reset.Add(in_AllTile->at(SearchColumn).m_MoveInfo.get());
		//�T����X�V
		SearchColumn--;
	}

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
	return (isFrontFin && isBackFin);
}


/****	���Z�b�g����	****/
bool MoveManager::ResetMove()
{
	if (Reset.Empty() == false)
	{
		Reset.ResetAll();
	}
	/*	�ړ��񂪂Ȃ��Ȃ�����	*/
	if (Reset.Empty() == true)
	{
		//�I���̎���true��Ԃ�
		return true;
	}
	return false;
}

