#include "ResetManager.h"
#include "TileColumn.h"
#include "Tile.h"
#include "Map.h"

/****	コンストラクタ	****/
ResetManager::ResetManager()
{
	m_ResetWaitTime = 0.0f;
	m_Timer = 0.0f;
}

/****	初期化処理	****/
bool ResetManager::Init()
{
	//タイル列全探索
	for (auto& Column : Map::m_TileColumnList)
	{
		//タイルリストがあるとき
		//スタート座標と移動しているとき
		if (Column.mp_TileList.empty() == false &&
			(Column.mp_TileList[0]->transform->Position.y != Column.mp_TileList[0]->GetStartPosition().y))
		{
			//リセットリストに格納する
			Reset.Add(Column.m_ResetInfo.get());
			//リセット情報初期化
			Reset.m_List.back()->Start();
		}
	}

	//リセット列があればtrueを返す
	if (Reset.Empty() == false)
	{
		m_Timer = 0.0f;
		m_ResetWaitTime = m_MaxResetWaitTime * (Reset.Num() / m_ResetMaxColumn);
		/*	移動SE再生	*/
		Sound::Sound_Play(SOUND_LABEL_MOVEBLOCK);

		return true;
	}
	//何もなければfalseを返す
	return false;
}

bool ResetManager::Update()
{
	cout << "リセット中\n";

	/*	リセット処理待ち	*/
	if (m_Timer < m_ResetWaitTime)
	{
		cout << "リセット処理待ち\n";
		//タイマー加算
		m_Timer += GameTimer::deltaTime();
		//リセット中はtrueを返す
		return true;
	}

	/*	リセット処理開始	*/
	auto itr = Reset.m_List.begin();
	/*	リセットリストを全更新	*/
	for (auto& ResetColumn : Reset.m_List)
	{
		bool ret = ResetColumn->Tick();

		//移動が終わった時
		if (/*ResetColumn->m_isFin == true*/ret == true)
		{
			cout << "リセット列削除\n";
			//リセット列を削除する
			itr = Reset.m_List.erase(itr);
		}
		else
		{
			//進める
			itr++;
		}
	}

	if (Reset.Empty() == true)
	{

		/*	全てのタイルを初期位置にする	*/
		//最後に無理やり初期位置に戻す
		Map::AllTileReset();
		cout << "全部リセット\n";
		//初期化処理
		Reset.Clear();
		m_Timer = 0.0f;
		m_ResetWaitTime = 0.0f;
		Map::m_isResetStart = false;
		Map::m_OnReset = false;
		return false;
	}

	//リセット中はtrueを返す
	return true;
}

bool ResetManager::ResetParticle()
{
	for (auto& column : Reset.m_List)
	{
		BlockParticleManager::DeleteMagicEffect(column->GetObjectID());
	}

	//終了したらtrueを返す
	return true;
}
