#pragma once
#include"Tile.h"
#include"ydmEngine.h"
#include"ChangeTileAnimController.h"

#define CHANGE_TIME 3000

class ChangeTile :public Tile
{
public:
	bool Start() override;
	bool Update() override;
	//bool Render()override;

private:
	//入れ替え色のパーターン
	enum Change_Pattern {
		CHANGE_3,
		CHANGE_4,
	};

	void Change3_AnimUpdate();//3色入れ替えアニメーション処理

	void Change4_AnimUpdate();//4色入れ替えアニメーション処理

	bool m_IsChanging;//入れ替え完了フラグ

	string m_NowTexture;//現在のテクスチャ

	string m_NextTexture;//入れ替え先のテクスチャ

	Change_Pattern m_Change_Pattern;

	ChangeTileAnimController m_ChangeTileController;

	float m_ChangeTimer;   //色が変わるまでの時間
};

