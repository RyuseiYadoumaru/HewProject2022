#include "MoveInfoList.h"

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

/****	�ړ�����	****/
bool MoveInfoList::MoveFront()
{
	bool isFin = false;
	//�ړ��Ȃ̂�1���ړ�������
	isFin = m_List.front()->Tick();
	/*	�ړ����I��������	*/
	if (isFin == true)
	{
		//�擪�z����폜����
		m_List.erase(m_List.begin());
	}
	return isFin;
}