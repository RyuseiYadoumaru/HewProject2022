//*****************************************************************************
//!	@file	Engine/Timer/GameTimer.cpp
//!	@brief	
//!	@note	�Q�[���^�C�}�[�N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "GameTimer.h"
#include "../Runtime/Application.h"
#include "../Runtime/Tools/SystemTimer.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
using namespace GameEngine;

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
float GameTimer::m_CurrenTime = 0.0f;
float GameTimer::m_OldTime = 0.0f;
float GameTimer::m_TotalFrameCnt = 0.0f;

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameTimer::GameTimer()
{
}

//==============================================================================
//!	@fn		Instance
//!	@brief	�Q�[���^�C�}�[����
//!	@retval	�C���X�^���X
//==============================================================================
GameTimer* GameTimer::Instance()
{
	static GameTimer Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	�Q�[���^�C�}�[������
//!	@retval	
//==============================================================================
void GameEngine::GameTimer::Init()
{
	//���݂̎��Ԃ��擾
	m_CurrenTime = (TIME)timeGetTime();
	m_OldTime = m_CurrenTime;
	//�Q�[���S�̂̃t���[���J�E���g
	m_TotalFrameCnt = 0;
}

//==============================================================================
//!	@fn		Update
//!	@brief	�Q�[���^�C�}�[�X�V
//!	@retval	
//==============================================================================
void GameEngine::GameTimer::Update()
{
	//�O�t���[���̎��ԑ��
	m_OldTime = m_CurrenTime;

	//���݂̎��Ԃ��擾
	m_CurrenTime = (TIME)timeGetTime();

	//�Q�[���S�̂̃t���[���J�E���g
	m_TotalFrameCnt++;
}

//==============================================================================
//!	@fn		deltaTime
//!	@brief	�f���^�^�C��
//!	@retval	�f���^�^�C��	
//==============================================================================
TIME GameEngine::GameTimer::deltaTime()
{
	return m_CurrenTime - m_OldTime;
}

//==============================================================================
//!	@fn		fixedDeltaTime
//!	@brief	�Œ�f���^�^�C��
//!	@retval	�Œ�f���^�^�C��	
//==============================================================================
TIME GameEngine::GameTimer::fixedDeltaTime()
{
	return (1.0f / Application::FPS) * 1000;
}

//==============================================================================
//!	@fn		NowTime
//!	@brief	���ݎ����擾
//!	@retval	���ݎ���	
//==============================================================================
TIME GameEngine::GameTimer::NowTime()
{
	return SystemTimer::Instance()->GetSystemTime();
}

//==============================================================================
//!	@fn		NowFrameCount
//!	@brief	���݂̃g�[�^���t���[����
//!	@retval	�g�[�^���t���[��
//==============================================================================
FRAME GameEngine::GameTimer::NowFrameCount()
{
	return m_TotalFrameCnt;
}

//==============================================================================
//!	@fn		ErrorFPS
//!	@brief	FPS�ُ̈�����m
//!	@param	
//!	@retval	true:�ُ�@false:����
//==============================================================================
bool GameEngine::GameTimer::ErrorFPS()
{
	return SystemTimer::Instance()->ErrorFPS();
}
