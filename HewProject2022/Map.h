#pragma once
#include "ydmEngine.h"
#include "Tile.h"
#include "TileColumn.h"
#include "MoveColumnInfo.h"

using Create::GameObject;

#define MAPSIZE_WIDTH	(unsigned int)(100)
#define COLUMN_NUM		(MAPSIZE_WIDTH)
#define MAPSIZE_HEIGHT	(unsigned int)(20)

class Map : public GameObject
{
public:
	Map();

	bool Start() override;
	bool Update() override;
	bool End() override;
	bool Render();

public:
	bool MoveMap(Tile* in_StandardTile);		//マップ移動処理
	void MoveSwicthON() { m_isMove = true; }	//移動処理起動
	void MoveSwicthOFF() { m_isMove = false; }	//移動処理終了
	bool GetisMove()const { return m_isMove; }	//移動フラグ取得

	TileColumn m_TileColumnList[COLUMN_NUM];	//1列タイルリスト

private:
	bool m_isMove;			//マップ移動フラグ
	bool m_isReturnMove;	//マップ移動戻すフラグ
	char* m_MapChip;
	float m_MoveTime;	//移動時間(1000ms = 1s)

	vector<MoveColumnInfo> m_MoveFrontColumnList;	//移動列格納配列(前)
	vector<MoveColumnInfo> m_MoveBackColumnList;	//移動列格納配列(後)
	vector<MoveColumnInfo> m_SaveMoveColumnList;	//移動列保存配列

private:
	void CreateTile(Vector2& in_Position, string FileName, MAPOBJ in_MapObj);		//タイル生成する	
	bool MoveTile();		//移動処理

	/*	移動列設定	*/
	void SetMoveFrontColumn(Tile& in_StandardTile);
	void SetMoveBackColumn(Tile& in_StandardTile);
	bool SetSaveColumn();

	bool MoveFrontColumn();		//前列移動
	bool MoveBackColumn();		//後列移動
	bool ReturnMoveColumn();	//列移動戻す
	void ResetColumnPos(vector<MoveColumnInfo>* out_ResetColumn);		//移動列リセット

};

