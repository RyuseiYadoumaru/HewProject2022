//*****************************************************************************
//!	@file	Engime/Runtime/Application.cpp
//!	@brief	
//!	@note	�A�v���P�[�V�����N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Application.h"
#include "Window/Window.h"
#include "Tools/Log.h"
#include "Tools/SystemTimer.h"
#include "Graphics/Shader.h"
#include "Engine.h"
#include "Graphics/DirectXGraphics.h"

#include <time.h>

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------

const char*		Application::WINDOW_TITLE = "TOY ALINE";
const char*		Application::WINDOW_CLASS_NAME = "#�f�}�`";

const uint32_t	Application::SCREEN_WIDTH = 1920;
const uint32_t	Application::SCREEN_HEIGHT = 1080;

const float		Application::FPS = 60.0f;

bool			Application::isShowCursor = false;
bool			Application::FullScreen = true;


//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
Application::Application()
{
	m_hWnd = NULL;
	m_hInstance = NULL;
	hr = NULL;
	isSucceed = FALSE;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	�C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
Application* Application::Instance()
{
	static Application Instance;

	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	�A�v���P�[�V����������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Application::Init(HINSTANCE hInstance)
{
	//���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �R���\�[�������蓖�Ă�
	AllocConsole();

	// �W���o�͂̊��蓖��
	freopen_s(&fp, "CON", "w", stdout);

	//�����_��������
	srand((unsigned int)time(NULL));

	Window* window = Window::Instance();


	/****	�E�B���h�E�̃p�����[�^�[�ݒ�	****/
	isSucceed = window->SetWindowParam(hInstance, WINDOW_CLASS_NAME, CS_CLASSDC);

	if (isSucceed == false)
	{
		Log::LogError("�A�v���P�[�V�����������Ɏ��s���܂���");
		return true;
	}

	/****	�E�B���h�E�쐬	****/
	isSucceed = window->SetWindow
	(
		WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		hInstance,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);

	if (isSucceed == false)
	{
		Log::LogError("�A�v���P�[�V�����������Ɏ��s���܂���");
		return false;
	}

	/****	DirectX11������	****/
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();

	bool sts = DirectXGraphic->Init(window->GetHandle(), SCREEN_WIDTH, SCREEN_HEIGHT, FullScreen);
	if (sts == false)
	{
		Log::LogError(window->GetHandle(), "DirectX�̏������Ɏ��s���܂���");
		return false;
	}

	/****	�n���h���f�[�^�擾	****/
	m_hWnd = window->GetHandle();

	/****	�}�E�X�J�[�\���\��	****/
	ShowCursor(isShowCursor);

	/****	�A�v���P�[�V�����C���X�^���X�擾	****/
	m_hInstance = hInstance;

	return true;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	���C�����[�v
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool Application::MainLoop()
{
	/****	�A�v���P�[�V��������	****/
	Log* log = Log::Instance();
	SystemTimer* systemtimer = SystemTimer::Instance();
	GameEngine::Engine* engine = GameEngine::Engine::Instance();

	/****	�G���W��������	****/
	bool Success = engine->Init();
	if (Success == false) return false;

	/****	�G���W���X�V	****/
	while (log->ExecMessage() == false && isEnd == false)
	{
		engine->Update();
		systemtimer->SystemWait(FPS);
		log->FPSWindowText(m_hWnd, systemtimer->GetNowFPS());

	}
	return true;
}

//==============================================================================
//!	@fn		Uninit
//!	@brief	�A�v���P�[�V�����I������
//!	@param	
//!	@retval	
//==============================================================================
void Application::Uninit()
{
	/****	�G���W���I������	****/
	GameEngine::Engine* engine = GameEngine::Engine::Instance();
	engine->Uninit();

	/****	�}�E�X�J�[�\���\��	****/
	ShowCursor(true);

	/****	DirectX���		****/
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();
	DirectXGraphic->Uninit();

	/****	�W���o�̓N���[�Y	****/
	fclose(fp);

	/****	�R���\�[�����	****/
	::FreeConsole();
}

//==============================================================================
//!	@fn		GetHandle
//!	@brief	�n���h���擾
//!	@param	
//!	@retval	�n���h��
//==============================================================================
HWND Application::GetHandle() const
{
	return m_hWnd;
}