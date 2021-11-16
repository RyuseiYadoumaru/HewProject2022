//*****************************************************************************
//!	@file	Engime/Runtime/WimMain.cpp
//!	@brief	Hal Event Week 2022 Project
//!	@brief	#�o��͂܂����̃}�b�`���O�A�v��
//!	@note	
//!	@author	YadoumaruRyusei	
//*****************************************************************************

#include "Application.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	���C���֐�
//!	@param�@hInstance     : ���̃A�v���P�[�V�����̃C���X�^���X�n���h��(���ʎq)
//!	@param	hPrevInstance : ���NULL(16bit����̖��c��)
//!	@param	lpCmdLine     : �R�}���h���C������󂯎���������ւ̃|�C���^
//!	@param	nCmdShow      : �A�v���P�[�V�����̏����E�C���h�E�\�����@�̎w��
//!	@retval	0
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/****	�A�v���P�[�V������	****/
	Application* App = Application::Instance();

	/****	�A�v���P�[�V����������	****/
	App->Init(hInstance);

	/****	�E�B���h�E�\��	****/
	ShowWindow(App->GetHandle(), nCmdShow);
	UpdateWindow(App->GetHandle());

	/****	���C������	****/
	App->MainLoop();

	/****	�A�v���P�[�V�����I������	****/
	App->Uninit();

	return 0;

}
