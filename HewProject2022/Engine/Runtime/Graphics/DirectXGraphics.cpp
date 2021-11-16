//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/DirectXGraphics.cpp
//!	@brief	
//!	@note	DirectXグラフィックに関する処理
//!	@author	YadoumaruRyusei
//*****************************************************************************


#include "DirectXGraphics.h"
#include "../../../directxtex/include/WICTextureLoader.h"
#include <locale.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")	

//==============================================================================
//!	@fn		Instance
//!	@brief	インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
DirectXGraphics* DirectXGraphics::Instance()
{
	static DirectXGraphics Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	ウィンドウハンドル
//!	@param	バックバッファXサイズ
//!	@param	バックバッファYサイズ
//!	@param	FullScreenフラグ
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool DirectXGraphics::Init(HWND hWnd, UINT in_ScreenWidth, UINT in_ScreenHeight, bool FullScreen)
{
	HRESULT	hr = S_OK;
	IDXGIFactory* factory;				// factory
	IDXGIAdapter* adapter;				// videocard
	IDXGIOutput* adapterOutput;			// monitor
	unsigned int numModes;
	unsigned int numerator = 60;		// 分子
	unsigned int denominator = 1;		// 分母
	DXGI_MODE_DESC* displayModeList;

	/****	スクリーンサイズ設定	****/
	ScreenWidth = in_ScreenWidth;
	ScreenHeight = in_ScreenHeight;

	/****	ドライバの種類	****/
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,			// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	unsigned int createDeviceFlags = 0;
	//   createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	/****	機能レベル	****/
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,					// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,					// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1					// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);


	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr))
	{
		return false;
	}

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr))
	{
		return false;
	}

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr))
	{
		return false;
	}

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr))
	{
		return false;
	}

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == ScreenWidth)
		{
			if (displayModeList[i].Height == ScreenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	delete[] displayModeList;
	displayModeList = NULL;

	adapterOutput->Release();
	adapterOutput = NULL;

	adapter->Release();
	adapter = NULL;

	factory->Release();
	factory = NULL;

	/****	スワップチェイン設定	****/
	// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
	// クラス　マルチサンプリング、リフレッシュレートが設定できる
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));					// ゼロクリア
	sd.BufferCount = 1;								// バックバッファの数
	sd.BufferDesc.Width = ScreenWidth;				// バックバッファの幅
	sd.BufferDesc.Height = ScreenHeight;			// バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// バックバッファフォーマット(R,G,B 範囲０．０から１．０)
	sd.BufferDesc.RefreshRate.Numerator = numerator;		// リフレッシュレート（分母）
	sd.BufferDesc.RefreshRate.Denominator = denominator;	// リフレッシュレート（分子）
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// バックバッファの使用方法
	sd.OutputWindow = hWnd;			// 関連付けるウインドウ
	sd.SampleDesc.Count = 1;		// マルチサンプルの数
	sd.SampleDesc.Quality = 0;		// マルチサンプルのクオリティ
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	/****	ウィンドウモード・フルスクリーンモード切替	****/
	if (FullScreen == true)
	{
		sd.Windowed = FALSE;	// ウインドウモード
	}
	else
	{
		sd.Windowed = TRUE;		// ウインドウモード
	}

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// モードの自動切り替え

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain
		(
			NULL,				// ディスプレイデバイスのアダプタ（ＮＵＬＬの場合最初に見つかったアダプタ）
			DriverType,			// デバイスドライバのタイプ
			NULL,				// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,	// デバイスフラグ
			featureLevels,		// 機能レベル
			numFeatureLevels,	// 機能レベル数
			D3D11_SDK_VERSION,	// 
			&sd,				// スワップチェインの設定
			&SwapChain,			// IDXGIDwapChainインタフェース	
			&D3d11Device,		// ID3D11Deviceインタフェース
			&FeatureLevel,		// サポートされている機能レベル
			&ImmediateContext	// デバイスコンテキスト
		);
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr))
	{
		return false;
	}

	/****	バックバッファ関係設定	****/
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	//レンダリングターゲット作成
	hr = D3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView);
	pBackBuffer->Release();
	pBackBuffer = NULL;
	if (FAILED(hr))
	{
		return false;
	}

	/****	深度ステンシルバッファ作成	****/
	D3D11_TEXTURE2D_DESC txDesc;

	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = ScreenWidth;
	txDesc.Height = ScreenHeight;
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;

	hr = D3d11Device->CreateTexture2D(&txDesc, NULL, &DepthStencilTexture);
	if (SUCCEEDED(hr))
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;
		hr = D3d11Device->CreateDepthStencilView(DepthStencilTexture.Get(), &dsDesc, &DepthStencilView);
	}
	if (FAILED(hr))
	{
		return false;
	}

	/****	レンダリングターゲット設定	****/
	//2DなのでZバッファ無効に設定
	ImmediateContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), NULL);

	/****	ビューポート設定	****/
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)ScreenWidth;
	viewport.Height = (FLOAT)ScreenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	ImmediateContext->RSSetViewports(1, &viewport);

	/****	ブレンドステート設定	****/
	D3D11_BLEND_DESC BlendDesc;

	// テクスチャ透過処理が行われるように設定
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	hr = D3d11Device->CreateBlendState(&BlendDesc, &BlendAlphaEnable);

	if (SUCCEEDED(hr))
	{
		ImmediateContext->OMSetBlendState(BlendAlphaEnable.Get(), blendFactor, 0xffffffff);
	}

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Uninit
//!	@brief	終了処理
//!	@param	
//!	@retval	
//==============================================================================
void DirectXGraphics::Uninit()
{
	ImmediateContext->ClearState();
	SwapChain->SetFullscreenState(false, nullptr);
}

//==============================================================================
//!	@fn		GetDevice
//!	@brief	D3d11デバイス取得
//!	@param	
//!	@retval	Device
//==============================================================================
ID3D11Device* DirectXGraphics::GetDevice() const
{

	return D3d11Device.Get();
}

//==============================================================================
//!	@fn		GetDeviceContext
//!	@brief	D3d11デバイスコンテキスト取得
//!	@param	
//!	@retval	ImmediateContext
//==============================================================================
ID3D11DeviceContext* DirectXGraphics::GetDeviceContext() const
{
	return ImmediateContext.Get();
}

//==============================================================================
//!	@fn		GetSwapChain
//!	@brief	スワップチェイン取得
//!	@param	
//!	@retval	SwapChain
//==============================================================================
IDXGISwapChain* DirectXGraphics::GetSwapChain() const
{
	return SwapChain.Get();
}

//==============================================================================
//!	@fn		GetRenderTargetView
//!	@brief	レンダリングターゲット取得
//!	@param	
//!	@retval	RenderTargetView
//==============================================================================
ID3D11RenderTargetView* DirectXGraphics::GetRenderTargetView() const
{
	return RenderTargetView.Get();
}
