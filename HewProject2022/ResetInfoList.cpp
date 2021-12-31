#include "ResetInfoList.h"

/****	追加処理	****/
void ResetInfoList::Add(ResetInfo* in_ResetInfo)
{
	m_List.push_back(in_ResetInfo);
}

/****	クリア処理	****/
void ResetInfoList::Clear()
{
	m_List.clear();
}

/****	リスト確認処理	****/
bool ResetInfoList::Empty()
{
	//リストの中身がない時はtrueを返す
	return m_List.empty();
}