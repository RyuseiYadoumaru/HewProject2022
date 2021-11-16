//*****************************************************************************
//!	@file	Engime/Runtime/Application.h
//!	@brief	
//!	@note	�A�v���P�[�V�����N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include <Windows.h>
#include <string>
#include<sstream>

/****	�A�v���P�[�V����	****/
class Application
{
public:

	static const char*		WINDOW_TITLE;				// �E�B���h�E�^�C�g��
	static const char*		WINDOW_CLASS_NAME;			// �N���X�l�[��

	static const uint32_t		SCREEN_WIDTH;				// �X�N���[������
	static const uint32_t		SCREEN_HEIGHT;				// �X�N���[���c��

	static const float			FPS;						// �t���[���J�E���g

private:

	HWND m_hWnd;				//Windows�n���h��
	HINSTANCE m_hInstance;		//�A�v���P�[�V��������

	HRESULT hr;					//�I���X�e�[�^�X
	BOOL isSucceed;				//��������I��

public:

	Application();

	static Application* Instance();

	bool Init(HINSTANCE hInstance);		//������

	bool MainLoop();

	void Uninit();		//�I������


	HWND GetHandle() const;


};