#pragma once
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_SELECT = 0,		// セレクトノイズ
	SOUND_LABEL_TITLE,			// タイトル
	SOUND_LABEL_WORLD1_GAMEBGM,	//ワールド1
	SOUND_LABEL_WORLD2_GAMEBGM,	//ワールド2
	SOUND_LABEL_WORLD3_GAMEBGM,	//ワールド3
	SOUND_LABEL_WORLD4_GAMEBGM,	//ワールド4
	SOUND_LABEL_WORLD5_GAMEBGM,	//ワールド5


	SOUND_LABEL__GOAL,			//ゴール


	SOUND_LABEL_ONGROUND,		// 着地SE
	SOUND_LABEL_MAGICBLOCK,		// 魔法ブロックSE
	SOUND_LABEL_MOVEBLOCK,		// 移動ブロックSE
	SOUND_LABEL_RESETBLOCK,		// リセットSE
	SOUND_LAVEL_SELECT_SE,		//選択SE
	SOUND_LABEL_OK,				// 決定SE
	SOUND_LABEL_BACK,			// 戻るSE
	SOUND_LABEL_GETSTAR,		// 星獲得SE
	SOUND_LABEL_SELECTWORLD,	// ワールドセレクトSE
	SOUND_LABEL_SHOOTINGSTAR,	// 流れ星SE



	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound
{
public:
	static HRESULT Sound_Init();     // 初期化
	static void Sound_Release();     // 解放

	static void Sound_Play(SOUND_LABEL label);     // 再生
	static void Sound_Stop(SOUND_LABEL label);     // 停止
};