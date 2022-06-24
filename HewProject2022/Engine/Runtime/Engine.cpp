//*****************************************************************************
//!	@file	Engine/Runtime/Engine.cpp
//!	@brief	
//!	@note	エンジンクラス
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
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
GameEngine::Engine::Engine()
{
	m_ConstanceBufferViewPort = nullptr;
}

//==============================================================================
//!	@fn		Instance
//!	@brief	エンジンインスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
GameEngine::Engine* GameEngine::Engine::Instance()
{
	static Engine Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	エンジン初期化
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::Engine::Init()
{
	DirectXGraphics* DirectXGraphic = DirectXGraphics::Instance();
	Application* App = Application::Instance();
	TransformMatrix* TransformMatrix = TransformMatrix::Instance();
	Log* log = Log::Instance();
	DataArray* data = DataArray::Instance();
	bool sts = false;

	/****	コンスタンスバッファ生成	****/

	ID3D11Device* device = DirectXGraphic->GetDevice();
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferViewPort), m_ConstanceBufferViewPort.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "ビューポートコンスタントバッファの生成に失敗しました");
		return false;
	}
	sts = SetViewPort(&Application::SCREEN_WIDTH, &Application::SCREEN_HEIGHT);
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "ビューポートのデータの転送に失敗しました");
		return false;
	}

	sts = TransformMatrix->Init();
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "行列コンスタントバッファの生成失敗しました");
		return false;
	}

	/****	データ初期化	****/
	sts = data->Init();
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "データの初期化に失敗しました");
		return false;
	}

	/****	サウンド初期化	****/
	HRESULT hr = Sound::Sound_Init();
	if (FAILED(hr))
	{
		Log::LogError(App->GetHandle(), "サウンドの初期化に失敗しました");
		return false;
	}

	/****	ゲームタイマー初期化	****/
	GameTimer::Init();

	return true;
}
//==============================================================================
//!	@fn		Update
//!	@brief	エンジン更新
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::Engine::Update()
{
	/****	インプット更新	****/
	Input::KeyUpdate();

	/****	シーン再生	****/
	switch (SceneManager::scene->GetState())
	{
		/*	初期化	*/
	case Create::Scene::START:
		sceneManager.SetUp();
		SceneManager::scene->Start();
		SceneManager::scene->SetUp();
		/*	再生	*/
	case Create::Scene::PLAY:
		SceneManager::scene->Update();
		SceneManager::scene->Render();
		break;

		/*	終了	*/
	case Create::Scene::END:
		SceneManager::scene->End();
		SceneManager::scene->SetState(Create::Scene::START);
		break;

	}

	return true;
}

//==============================================================================
//!	@fn		Uninit
//!	@brief	エンジン終了処理
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::Engine::Uninit()
{

	/****	シーンマネージャー解放	****/
	sceneManager.Releace();

	/****	サウンド解放	****/
	Sound::Sound_Release();

	return true;
}


//==============================================================================
//!	@fn		SetVewPort
//!	@brief	定数バッファにスクリーンサイズをセットする
//!	@param	
//!	@retval	true:正常終了　false:異常終了
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
