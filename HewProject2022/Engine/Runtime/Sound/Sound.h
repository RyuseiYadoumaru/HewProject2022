#pragma once
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001,			// �T���v��BGM
	SOUND_LABEL_WORLD1_GAMEBGM,	//���[���h1
	SOUND_LABEL_WORLD2_GAMEBGM,	//���[���h2
	SOUND_LABEL_WORLD3_GAMEBGM,	//���[���h3
	SOUND_LABEL_WORLD5_GAMEBGM,	//���[���h5
	SOUND_LABEL_ONGROUND,		// ���nSE
	SOUND_LABEL_MAGICBLOCK,		// ���@�u���b�NSE
	SOUND_LABEL_MOVEBLOCK,		// �ړ��u���b�NSE
	SOUND_LABEL_RESETBLOCK,		// ���Z�b�gSE

	SOUND_LABEL_MAX,
} SOUND_LABEL;

class Sound
{
public:
	static HRESULT Sound_Init();     // ������
	static void Sound_Release();     // ���

	static void Sound_Play(SOUND_LABEL label);     // �Đ�
	static void Sound_Stop(SOUND_LABEL label);     // ��~
};