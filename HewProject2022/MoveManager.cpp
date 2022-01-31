#include "MoveManager.h"
#include "LandTile.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveInfo.h"
#include "Map.h"

/****	静的メンバ変数	****/
float MoveManager::NowFinFrontMoveColumn = 0;
float MoveManager::NowFinBackMoveColumn = 0;


/****	コンストラクタ	****/
MoveManager::MoveManager()
{
	m_MoveWaitTime = 0.0f;
	m_Timer = 0.0f;
	FrontCounter = 0;
	BackCounter = 0;
	EffectColor = BlockEffectColor::BLUE;
	isMagicFin = false;
	//エフェクト配列初期化
	FrontParticle.Clear();
	BackParticle.Clear();
	ResetBeforeList.Clear();
	HitCeilingColumn = NULL;
	isResetBefore = false;
	isHitCeiling = false;
	SaveHitFrame = 0;
	ResetColumnNum.clear();
}

/****	初期化	****/
bool MoveManager::Init(LandTile* in_StandardTile)
{

	NowFinFrontMoveColumn = 0;
	NowFinBackMoveColumn = 0;
	//移動するブロックがあるときはtrueで返す


	/*	移動列bool初期化	*/
	Front.isBack = false;
	Back.isBack = true;
	/*	基準タイル設定	*/
	m_StandardTile = in_StandardTile;

	//移動配列に格納
	if (SetMoveList() == true)
	{
		//タイマー初期化
		m_Timer = 0.0f;

		//エフェクト用カウンタ初期化
		FrontCounter = 0;
		BackCounter = 0;
		//エフェクトカラー設定
		if (m_StandardTile->GetLandTile()->GetKind() == C1 ||
			m_StandardTile->GetLandTile()->GetKind() == C4)
		{
			//赤系のブロックなら、エフェクトカラーを赤に設定
			EffectColor = BlockEffectColor::RED;
			isMagicFin = false;
		}
		return true;
	}
	return false;
}

/****	更新	****/
bool MoveManager::Update()
{
	bool isFin = false;
	/****	移動処理	****/
	//普通の移動処理
	if (isResetBefore == false)
	{
		if (Front.Empty() == false ||
			Back.Empty() == false)
		{
			/*	リセット処理再生	*/
			if (isResetFin == false)
			{
				SetResetParticle();
				isResetFin = true;
				//BlockParticleManager::CreateMagicEffect(m_StandardTile->GetLandTile(), EffectColor);

			}
			//移動リストが空じゃないとき

			if (isMagicFin == true || SetMagicParticle() == true)
			{
				//待機時間分まつ
				isFin = Move();
				Input::Vibration(6000.0f);
			}

			else
			{
				m_Timer += GameTimer::deltaTime();
			}
		}
		else
		{
			m_Timer = 0.0f;
			isFin = true;
		}

	}
	/*	リセット処理	*/
	else
	{
		if (ResetBeforeList.Empty() == false)
		{
			/*	リセット処理再生	*/
			if (isResetFin == false)
			{
				SetResetParticle();
				for (auto& reset : ResetBeforeList.m_List)
				{
					reset->SetMoveBeforePos();
				}
				isResetFin = true;
				//BlockParticleManager::CreateMagicEffect(m_StandardTile->GetLandTile(), EffectColor);

			}
			//移動リストが空じゃないとき

			if (isMagicFin == true || SetMagicParticle() == true)
			{
				//天井にぶつかるときの移動処理
				isFin = MoveResetBefore();
			}
			else
			{
				m_Timer += GameTimer::deltaTime();
			}

		}
		else
		{
			m_Timer = 0.0f;
			isFin = true;
		}
	}

	//終了の時はtrueを返す
	return isFin;
}


/****	乗ってるオブジェクトの名前取得	****/
string & MoveManager::GetLandObjectName()
{
	return m_StandardTile->GetOwnerName();
}

/****	乗っているオブジェクトのID取得する	****/
int MoveManager::GetLandObjectID() const
{
	return (int)m_StandardTile->GetOwnerID();
}


//-----------------------------------------------------------------------------
// Private Function
//-----------------------------------------------------------------------------

/****	移動リスト作成	****/
bool MoveManager::SetMoveList()
{
	//移動列があるときはtrueを返す

	/****	基準列設定	****/
	int NowColumn = (int)m_StandardTile->GetLandTile()->GetMyColumn();
	//乗ってる列の基準列を入れておく
	Map::m_TileColumnList[NowColumn].m_MoveInfo->SetStandardTile(m_StandardTile->GetLandTile());
	ResetColumnNum.push_back(NowColumn);
	/****	前探索	****/
	/*	スタート探索列	*/
	int SearchColumn = NowColumn + 1;

	/*	探索処理	*/
	while (Map::m_TileColumnList[SearchColumn].m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//リセット列保存
		ResetColumnNum.push_back(SearchColumn);
		//エフェクト用配列格納
		FrontParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());

		/*	現在のポジションと違う場所に移動するとき	*/
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//移動列格納
			Front.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
			//リセット確認
			if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->JudgeResetBeforePos() == true)
			{
				//リセットのフラグを立てる
				isResetBefore = true;
				SetHitCeilingColumn(Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetHeadTile()->GetMyColumn());
			}
		}
		//探索列更新
		SearchColumn++;
	}

	/****	後探索	****/
	/*	スタート探索列	*/
	SearchColumn = NowColumn - 1;
	/*	探索処理	*/
	while (Map::m_TileColumnList[SearchColumn].m_MoveInfo->SearchTile(m_StandardTile->GetLandTile()))
	{
		//リセット列保存
		ResetColumnNum.push_back(SearchColumn);
		//エフェクト用配列格納
		BackParticle.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());

		/*	現在のポジションと違う場所に移動するとき	*/
		if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetPositionEqual() == false)
		{
			//移動列格納
			Back.Add(Map::m_TileColumnList[SearchColumn].m_MoveInfo.get());
			//リセット確認
			if (Map::m_TileColumnList[SearchColumn].m_MoveInfo->JudgeResetBeforePos() == true)
			{
				//リセットのフラグを立てる
				isResetBefore = true;
				SetHitCeilingColumn(Map::m_TileColumnList[SearchColumn].m_MoveInfo->GetHeadTile()->GetMyColumn());
			}
		}
		//探索列更新
		SearchColumn--;
	}


	//天井に当たっていないとき
	if (isResetBefore == false)
	{
		//前か後ろに移動列があるときはtrueを返す
		if (Back.Empty() == false || Front.Empty() == false) return true;
		//何もない時はfalseを返す
		return false;
	}

	//天井に当たっているとき
	//移動列を保存する
	ResetBeforeList.m_List = Front.m_List;
	if (ResetBeforeList.Empty() == false)
	{
		copy(Back.m_List.begin(), Back.m_List.end(), back_inserter(ResetBeforeList.m_List));
	}
	else
	{
		ResetBeforeList.m_List = Back.m_List;

	}
	return true;
}

/****	移動処理	****/
bool MoveManager::Move()
{
	/*	終了フラグ	*/
	bool isFrontFin = false;
	bool isBackFin = false;

	/*	前移動	*/
	if (Front.Empty() == false)
	{
		/*	列移動処理	*/
		Front.MoveFront();

	}

	/*	移動列がなくなったら	*/
	if (Front.Empty() == true)
	{
		//終了flagを立てておく
		isFrontFin = true;
	}

	/*	後移動	*/
	if (Back.Empty() == false)
	{
		Back.MoveFront();
	}

	/*	移動列がなくなったら	*/
	if (Back.Empty() == true)
	{
		//終了flagを立てておく
		isBackFin = true;
	}

	//終了の時はtrueを返す
	if (isFrontFin == true && isBackFin == true)
	{
		//移動パーティクル再生
		SetMoveParticle();
		return true;
	}
	return false;
}

/****	天井に当たるときの移動処理	****/
bool MoveManager::MoveResetBefore()
{
	bool isFin = false;
	/*	リセットリストが空じゃないとき	*/
	if (ResetBeforeList.Empty() == false)
	{
		/*	終わった列がリセット列に該当していないとき	*/
		if (NowFinFrontMoveColumn != HitCeilingColumn &&
			NowFinBackMoveColumn != HitCeilingColumn)
		{
			/*	前移動	*/
			if (Front.Empty() == false)
			{
				/*	列移動処理	*/
				Front.MoveFront();
			}

			/*	後移動	*/
			if (Back.Empty() == false)
			{
				/*	列移動処理	*/
				Back.MoveFront();
			}
		}

		/*	前の座標に戻す処理	*/
		else
		{
			//終わった列が天井と当たる列に該当するとき
			isFin = ResetBefore();
		}


	}

	if (isFin == true)
	{
		for (auto& tile : FrontParticle.m_List)
		{
			BlockParticleManager::MagicReset(*tile->GetStandartdTile());
		}
		for (auto& tile : BackParticle.m_List)
		{
			BlockParticleManager::MagicReset(*tile->GetStandartdTile());
		}

		/*	終了処理	*/
		Front.Clear();
		Back.Clear();
		ResetBeforeList.Clear();
		HitCeilingColumn = 0;
		NowFinFrontMoveColumn = 0;
		NowFinBackMoveColumn = 0;
		//終了の時はtrueを返す
		return true;
	}
	return false;
}


/****	マジックエフェクトを再生する	****/
bool MoveManager::SetMagicParticle()
{
	//待機時間が終了したら
	//エフェクトを1つずつ再生していく
	if (m_Timer <= m_OneMagicWaitTime)
	{
		return false;
	}
	m_Timer = 0.0f;

	if (FrontParticle.Num() != 0 && FrontCounter < FrontParticle.Num())
	{
		//前の基準ブロックにエフェクトをかける
		BlockParticleManager::CreateMagicEffect(FrontParticle.m_List[FrontCounter]->GetStandartdTile(), EffectColor);
		FrontCounter++;
	}

	if (BackParticle.Num() != 0 && BackCounter < BackParticle.Num())
	{
		//後の基準ブロックにエフェクトをかける
		BlockParticleManager::CreateMagicEffect(BackParticle.m_List[BackCounter]->GetStandartdTile(), EffectColor);
		BackCounter++;
	}

	/*	両方とも終了	*/
	if (BackCounter >= BackParticle.Num() && FrontCounter >= FrontParticle.Num())
	{
		//再生が終了したらtrueを返す
		isMagicFin = true;
		return true;
	}

	//終了していない
	return false;
}


/****	移動エフェクト再生	****/
void MoveManager::SetMoveParticle()
{

	//全て移動が完了したら
	//一斉に再生する
	for (auto& front : FrontParticle.m_List)
	{
		Tile* PTile = front->GetStandartdTile();
		BlockParticleManager::DeleteMagicEffect(PTile->GetId().x);
		BlockParticleManager::CreateMoveEffect(PTile, EffectColor);
	}
	for (auto& Back : BackParticle.m_List)
	{
		Tile* PTile = Back->GetStandartdTile();
		BlockParticleManager::DeleteMagicEffect(PTile->GetId().x);
		BlockParticleManager::CreateMoveEffect(PTile, EffectColor);
	}

}

/****	リセット処理再生	****/
void MoveManager::SetResetParticle()
{

	/*	移動している全てのタイルを探索	*/
	for (auto num : ResetColumnNum)
	{
		for (auto& tile : Map::m_TileColumnList[num].mp_TileList)
		{
			//移動エフェクトがデリートされたら
			if (BlockParticleManager::DeleteMoveEffect(tile->GetId().x) == true)
			{

				//リセットエフェクトをかける
				if (BlockParticleManager::JudgeRedorBlue(tile->GetKind()) == EFFECT_RED)
				{
					BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::RED);
				}
				else
				{
					BlockParticleManager::CreateResetEffect(tile, BlockEffectColor::BLUE);
				}
			}

		}
	}

}


/****	天井に当たる列	****/
void MoveManager::SetHitCeilingColumn(float column)
{
	if (HitCeilingColumn == NULL)
	{
		HitCeilingColumn = column;
		return;
	}
	/*	間隔チェック	*/
	float land = m_StandardTile->GetNowColumn();
	float NowDis = fabsf(land - HitCeilingColumn);
	float CheckDis = fabsf(land - column);

	//乗ってる位置から近いほうを採用
	if (NowDis > CheckDis) HitCeilingColumn = column;

}

bool MoveManager::ResetBefore()
{
	/*	リセット処理開始	*/
	auto itr = ResetBeforeList.m_List.begin();
	/*	リセットリストを全更新	*/
	for (auto& reset : ResetBeforeList.m_List)
	{
		bool ret = reset->ResetTick();

		//移動が終わった時
		if (/*ResetColumn->m_isFin == true*/ret == true)
		{
			for (auto& reset : ResetBeforeList.m_List)
			{
				reset->ResetBeforePosition();
			}
			//リセット列を削除する
			itr = ResetBeforeList.m_List.erase(itr);
		}
		else
		{
			//進める
			itr++;
		}
	}
	if (ResetBeforeList.Empty() == false)
	{
		return false;
	}

	return true;
}
