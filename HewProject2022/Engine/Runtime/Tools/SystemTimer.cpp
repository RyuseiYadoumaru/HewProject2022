//*****************************************************************************
//!	@file	Engine/Runtime/Tools/SystemTimer.cpp
//!	@brief	
//!	@note	�V�X�e���^�C�}�[�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "SystemTimer.h"
#include "../Application.h"
#include "../../Timer/GameTimer.h"
#include "Log.h"
#pragma comment(lib, "winmm.lib")

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
SystemTimer::SystemTimer()
{
	GetLocalTime(&m_SystemLocalTime);

	m_SystemStartTime = (float)timeGetTime();
	m_WaitTime = 0.0f;
	m_SaveTime = 0.0f;
	m_SystemCounter = 0;

	m_NowFPS = 60;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	�V�X�e���^�C�}�[����
//!	@retval	�C���X�^���X
//==============================================================================
SystemTimer* SystemTimer::Instance()
{
	static SystemTimer Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		SystemWait
//!	@brief	�����҂�
//!	@param	FPS
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool SystemTimer::SystemWait(const float FPS)
{
	float BaseTime = GetSystemTime() + 1;

	//�����҂�����
	m_WaitTime = m_SystemCounter * 1000 / FPS - BaseTime;


	//�����҂�
	if (m_WaitTime > 0)
	{
		Sleep((DWORD)m_WaitTime);
	}
	else
	{
		Sleep(1 / Application::FPS);
	}

	//�t���[���J�E���g
	m_SystemCounter++;

	//�Q�[���^�C�}�[�X�V
	GameEngine::GameTimer::Update();

	return true;
}

//==============================================================================
//!	@fn		GetSystemCurrentTime
//!	@brief	�V�X�e�����ݎ����擾
//!	@param	
//!	@retval	���ݎ����~���b
//==============================================================================
float SystemTimer::GetSystemCurrentTime() const
{
	return (float)timeGetTime();
}

//==============================================================================
//!	@fn		GetSystemTime
//!	@brief	�V�X�e���o�ߎ��Ԏ擾
//!	@param	
//!	@retval	�o�ߎ��ԃ~���b
//==============================================================================
float SystemTimer::GetSystemTime()
{
	return GetSystemCurrentTime() - m_SystemStartTime;
}

//==============================================================================
//!	@fn		GetNowFPS
//!	@brief	���݂̃t���[�����[�g�擾
//!	@param	
//!	@retval	���݂̃t���[�����[�g
//==============================================================================
float SystemTimer::GetNowFPS()
{
	int IntervalFrame = 30;

	/*	FPS�v��	*/
	if (m_SystemCounter % IntervalFrame == 0)
	{
		float CurrentTime = GetSystemTime();


		m_NowFPS = IntervalFrame * 1000.0f / (CurrentTime - m_SaveTime);
		m_SaveTime = CurrentTime;

	}

	return m_NowFPS;
}

//==============================================================================
//!	@fn		GetNowFPS
//!	@brief	���݂̃t���[�����[�g�擾
//!	@param	�C���^�[�o��
//!	@retval	���݂̃t���[�����[�g
//==============================================================================
float SystemTimer::GetNowFPS(int in_Interval)
{
	int IntervalFrame = in_Interval;

	/*	FPS�v��	*/
	if (m_SystemCounter % IntervalFrame == 0)
	{
		float CurrentTime = GetSystemTime();


		m_NowFPS = IntervalFrame * 1000.0f / (CurrentTime - m_SaveTime);
		m_SaveTime = CurrentTime;

	}

	return m_NowFPS;
}

//==============================================================================
//!	@fn		ErrorFPS
//!	@brief	FPS�ُ̈�����m
//!	@param	
//!	@retval	true:�ُ�@false:����
//==============================================================================
bool SystemTimer::ErrorFPS()
{
	//fps�͈�
	float Min = Application::FPS - ErrorFPSRange;
	float Max = Application::FPS + ErrorFPSRange;

	//�ُ�`�F�b�N
	if (m_NowFPS < Min || m_NowFPS > Max) return true;

	//����
	return false;
}

//==============================================================================
//!	@fn		CheckSytemWait
//!	@brief	�����҂��m�F
//!	@param	FPS
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool SystemTimer::CheckSystemWait(const float FPS)
{
	/****	�҂����Ԋm�F	****/
	float CheckMaxWaitTime = (1 / FPS) * 2;
	float CheckMinWaitTime = (1 / FPS) / 2;
	if (m_WaitTime > CheckMaxWaitTime || m_WaitTime < CheckMinWaitTime) return false;

	/****	�o�ߎ��Ԋm�F	****/
	if (GetSystemTime() <= 0) return false;

	/****	�V�X�e���J�E���^�m�F	****/
	if (m_SystemCounter == NULL) return false;

	/****	����FPS�m�F	****/
	if (m_NowFPS > FPS * 1.2 || m_NowFPS < FPS * 0.7) return false;
	return true;
}
