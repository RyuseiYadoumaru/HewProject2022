#pragma once
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	SOUND_LABEL_BGM001,			// サンプルBGM
	SOUND_LABEL_WORLD1_GAMEBGM,	//ワールド1
	SOUND_LABEL_WORLD2_GAMEBGM,	//ワールド2
	SOUND_LABEL_WORLD3_GAMEBGM,	//ワールド3
	SOUND_LABEL_WORLD5_GAMEBGM,	//ワールド5
	SOUND_LABEL_ONGROUND,		// 着地SE
	SOUND_LABEL_MAGICBLOCK,		// 魔法ブロックSE
	SOUND_LABEL_MOVEBLOCK,		// 移動ブロックSE
	SOUND_LABEL_RESETBLOCK,		// リセットSE

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