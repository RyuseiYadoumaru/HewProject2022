//*****************************************************************************
//!	@file	Engine/Runtime/Engine.cpp
//!	@brief	
//!	@note	�G���W���N���X
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "Engine.h"
#include "Application.h"
#include "Graphics/Shader.h"
#include "Graphics/DirectXGraphics.h"
#include "Core/TransformMatrix.h"
#include "Tools/Log.h"
#include "../Input/Input.h"
#include "../Data/DataArray.h"
#include "Sound/Sound.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	�R���X�g���N�^
//!	@param	
//==============================================================================
GameEngine::Engine::Engine()
{
	m_ConstanceBufferViewPort = nullptr;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	�G���W���C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
GameEngine::Engine* GameEngine::Engine::Instance()
{
	static Engine Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	�G���W��������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Engine::Init()
{
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();
	Application* App = Application::Instance();
	TransformMatrix* TransformMatrix = TransformMatrix::Instance();
	Log* log = Log::Instance();
	DataArray* data = DataArray::Instance();
	bool sts = false;

	/****	�R���X�^���X�o�b�t�@����	****/

	ID3D11Device* device = DirectXGraphic->GetDevice();
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferViewPort), m_ConstanceBufferViewPort.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "�r���[�|�[�g�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���");
		return false;
	}
	sts = SetViewPort(&Application::SCREEN_WIDTH, &Application::SCREEN_HEIGHT);
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "�r���[�|�[�g�̃f�[�^�̓]���Ɏ��s���܂���");
		return false;
	}

	sts = TransformMatrix->Init();
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "�s��R���X�^���g�o�b�t�@�̐������s���܂���");
		return false;
	}

	/****	�f�[�^������	****/
	sts = data->Init();
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "�f�[�^�̏������Ɏ��s���܂���");
		return false;
	}

	/****	�T�E���h������	****/
	HRESULT hr = Sound::Sound_Init();
	if (FAILED(hr))
	{
		Log::LogError(App->GetHandle(), "�T�E���h�̏������Ɏ��s���܂���");
		return false;
	}

	/****	�Q�[���^�C�}�[������	****/
	GameTimer::Init();

	return true;
}
//==============================================================================
//!	@fn		Update
//!	@brief	�G���W���X�V
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Engine::Update()
{
	/****	�C���v�b�g�X�V	****/
	Input::KeyUpdate();

	/****	�V�[���Đ�	****/
	switch (SceneManager::scene->GetState())
	{
		/*	������	*/
	case Create::Scene::START:
		sceneManager.SetUp();
		SceneManager::scene->Start();
		SceneManager::scene->SetUp();
		/*	�Đ�	*/
	case Create::Scene::PLAY:
		SceneManager::scene->Update();
		SceneManager::scene->Render();
		break;

		/*	�I��	*/
	case Create::Scene::END:
		SceneManager::scene->End();
		SceneManager::scene->SetState(Create::Scene::START);
		break;

	}

	return true;
}

//==============================================================================
//!	@fn		Uninit
//!	@brief	�G���W���I������
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Engine::Uninit()
{

	/****	�V�[���}�l�[�W���[���	****/
	sceneManager.Releace();

	/****	�T�E���h���	****/
	Sound::Sound_Release();

	return true;
}


//==============================================================================
//!	@fn		SetVewPort
//!	@brief	�萔�o�b�t�@�ɃX�N���[���T�C�Y���Z�b�g����
//!	@param	
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool GameEngine::Engine::SetViewPort(const uint32_t* Width, const uint32_t* Height)
{
	ID3D11DeviceContext* DeviceContext = DirectXGraphics::Instance()->GetDeviceContext();
	bool sts = false;


	D3D11_MAPPED_SUBRESOURCE Date;
	HRESULT hr = DeviceContext->Map(m_ConstanceBufferViewPort.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Date);

	if (SUCCEEDED(hr))
	{
		ConstanceBufferViewPort View = { 0 };
		View.ScreenWidth[0] = *Width;
		View.ScreenHeight[0] = *Height;
		memcpy_s(Date.pData, Date.RowPitch, &View, sizeof(ConstanceBufferViewPort));

		DeviceContext->Unmap(m_ConstanceBufferViewPort.Get(), 0);
		sts = true;
	}

	DeviceContext->PSSetConstantBuffers(0, 1, m_ConstanceBufferViewPort.GetAddressOf());
	DeviceContext->VSSetConstantBuffers(0, 1, m_ConstanceBufferViewPort.GetAddressOf());
	return sts;
}
