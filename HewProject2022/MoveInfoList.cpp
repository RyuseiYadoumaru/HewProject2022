#include "MoveInfoList.h"
#include "Tile.h"
#include "MoveManager.h"

/****	�ǉ�����	****/
void MoveInfoList::Add(MoveInfo* in_MoveInfo)
{
	m_List.push_back(in_MoveInfo);
}

/****	�N���A����	****/
void MoveInfoList::Clear()
{
	m_List.clear();
}

/****	���X�g�m�F����	****/
bool MoveInfoList::Empty()
{
	//���X�g�̒��g���Ȃ�����true��Ԃ�
	return m_List.empty();
}

int MoveInfoList::Num()
{
	return m_List.size();
}

/****	�擪��	****/
float MoveInfoList::FrontColumn()
{
	if (m_List.empty() == false)
	{
		//�擪�^�C���̗��Ԃ�
		return m_List.front()->GetHeadTile()->GetMyColumn();
	}
	return NULL;
}

/****	�ړ�����	****/
bool MoveInfoList::MoveFront()
{
	bool isFin = false;
	//�ړ��Ȃ̂�1���ړ�������
	isFin = m_List.front()->Tick();
	/*	�ړ����I��������	*/
	if (isFin == true)
	{
		if (isBack == true)
			MoveManager::NowFinBackMoveColumn = m_List.front()->GetHeadTile()->GetMyColumn();
		else
			MoveManager::NowFinFrontMoveColumn = m_List.front()->GetHeadTile()->GetMyColumn();
		//�擪�z����폜����
		m_List.erase(m_List.begin());
	}
	return isFin;
}