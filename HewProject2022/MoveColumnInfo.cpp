#include "MoveColumnInfo.h"

/****	コンストラクタ	****/
MoveColumnInfo::MoveColumnInfo()
{
	mp_MoveColumun = nullptr;
	m_Speed = 1.0f;
	m_MoveValue = 0.0f;
	m_NowMoveValue = 0.0f;
	m_isUp = true;
}

/****	移動処理	****/
void MoveColumnInfo::Move()
{
	SystemTimer* Timer = SystemTimer::Instance();
	if (m_NowMoveValue == m_MoveValue)
	{
		return;
	}
	float VectorY = m_Speed * Timer->DeltaTime();
	m_NowMoveValue += VectorY;

	/*	上昇処理	*/
	if (m_isUp == true)
	{
		if (m_NowMoveValue <= m_MoveValue)
		{
			cout << "上昇移動量：";
			cout << m_NowMoveValue << endl;

			//移動量補正
			VectorY += m_MoveValue - m_NowMoveValue;
			m_NowMoveValue = m_MoveValue;
		}
	}

	/*	下降処理	*/
	else
	{
		if (m_NowMoveValue >= m_MoveValue)
		{
			cout << "下降移動量：";
			cout << m_NowMoveValue << endl;

			//移動量補正
			VectorY += m_MoveValue - m_NowMoveValue;
			m_NowMoveValue = m_MoveValue;

		}
	}

	//現在の移動量
	mp_MoveColumun->Move(VectorY);
}


/****	移動列設定	****/
void MoveColumnInfo::SetMoveColumun(TileColumn* in_Columun)
{
	mp_MoveColumun = in_Columun;
}

/****	スピード設定	****/
void MoveColumnInfo::SetSpeed(float in_Speed)
{
	m_Speed = in_Speed;
}

/****	移動量設定	****/
void MoveColumnInfo::SetMoveValue(float in_MoveValue)
{
	m_MoveValue = in_MoveValue;
}

/****	基準タイル設定	****/
void MoveColumnInfo::SetStandardTile(Tile* in_Standard)
{
	m_StandardTile = in_Standard;
}


/****	リセット時の移動量	****/
float MoveColumnInfo::ResetMoveValue()
{
	return 	m_StandardTile->GetStartPosition().y - m_StandardTile->transform->Position.y;
}
