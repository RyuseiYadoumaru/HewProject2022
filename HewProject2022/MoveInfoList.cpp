#include "MoveInfoList.h"

/****	追加処理	****/
void MoveInfoList::Add(MoveInfo* in_MoveInfo)
{
	m_List.push_back(in_MoveInfo);
}

/****	クリア処理	****/
void MoveInfoList::Clear()
{
	m_List.clear();
}

/****	リスト確認処理	****/
bool MoveInfoList::Empty()
{
	//リストの中身がない時はtrueを返す
	return m_List.empty();
}

/****	移動処理	****/
bool MoveInfoList::MoveFront()
{
	bool isFin = false;
	//移動なので1個ずつ移動させる
	isFin = m_List.front()->Tick();
	/*	移動が終了したら	*/
	if (isFin == true)
	{
		//先頭配列を削除する
		m_List.erase(m_List.begin());
	}
	return isFin;
}