#pragma once
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	SOUND_LABEL_BGM001,			// �T���v��BGM
	SOUND_LABEL_WORLD1_GAMEBGM,	//���[���h�P
	SOUND_LABEL_SE000,			// �T���v��SE
	SOUND_LABEL_SE001,			// �T���v��SE
	SOUND_LABEL_SE002,			// �T���v��SE
	SOUND_LABEL_SE003,			// �T���v��SE
	SOUND_LABEL_SE004,			// �T���v��SE
	SOUND_LABEL_SE005,			// �T���v��SE
	SOUND_LABEL_SE006,			// �T���v��SE
	SOUND_LABEL_SE007,			// �T���v��SE
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