#include "ResetInfoList.h"

/****	�ǉ�����	****/
void ResetInfoList::Add(ResetInfo* in_ResetInfo)
{
	m_List.push_back(in_ResetInfo);
}

/****	�N���A����	****/
void ResetInfoList::Clear()
{
	m_List.clear();
}

/****	���X�g�m�F����	****/
bool ResetInfoList::Empty()
{
	//���X�g�̒��g���Ȃ�����true��Ԃ�
	return m_List.empty();
}