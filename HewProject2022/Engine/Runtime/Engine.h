//*****************************************************************************
//!	@file	Engine/Runtime/Engine.h
//!	@brief	
//!	@note	エンジンクラス
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once

#include "../SceneManager/SceneManager.h"
#include "Tools/macro.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
namespace GameEngine
{
	class Engine
	{
	public:
		/****	定数バッファ定義	****/
		//ビューポート
		ALIGN16 struct ConstanceBufferViewPort
		{
			uint32_t ScreenWidth[4];
			uint32_t ScreenHeight[4];
		};

	private:

		SceneManager sceneManager;

	private:

		ComPtr<ID3D11Buffer> m_ConstanceBufferViewPort;

	public:

		Engine();

		static Engine* Instance();

		bool Init();

		bool Update();

		bool Uninit();

	private:
		bool SetViewPort(const uint32_t* Width, const uint32_t* Height);
	};


}