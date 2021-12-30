#pragma once
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	SOUND_LABEL_BGM001,			// サンプルBGM
	SOUND_LABEL_WORLD1_GAMEBGM,	//ワールド１
	SOUND_LABEL_SE000,			// サンプルSE
	SOUND_LABEL_SE001,			// サンプルSE
	SOUND_LABEL_SE002,			// サンプルSE
	SOUND_LABEL_SE003,			// サンプルSE
	SOUND_LABEL_SE004,			// サンプルSE
	SOUND_LABEL_SE005,			// サンプルSE
	SOUND_LABEL_SE006,			// サンプルSE
	SOUND_LABEL_SE007,			// サンプルSE
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