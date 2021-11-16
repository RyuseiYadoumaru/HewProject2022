//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/DirectXGraphics.h
//!	@brief	
//!	@note	DirectXグラフィックに関する処理
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;

class DirectXGraphics
{
private:
	ComPtr<ID3D11Device>			D3d11Device;		//Direct3Dデバイス
	ComPtr<ID3D11DeviceContext>		ImmediateContext;	//Direct3Dデバイスコンテキスト
	ComPtr<IDXGISwapChain>			SwapChain;			//スワップチェイン
	ComPtr<ID3D11RenderTargetView>	RenderTargetView;	//レンダーターゲットビュー

	ComPtr<ID3D11Texture2D>			DepthStencilTexture;//Zバッファ、ステンシルバッファ
	ComPtr<ID3D11DepthStencilView>	DepthStencilView;	//Zバッファ、ステンシルビュー

	ComPtr<ID3D11BlendState>		BlendAlphaEnable;	//ブレンド状態

	D3D_DRIVER_TYPE					DriverType;			//ドライバタイプ
	D3D_FEATURE_LEVEL				FeatureLevel;		//機能レベル

	UINT							ScreenWidth;		//バックバッファXサイズ
	UINT							ScreenHeight;		//バックバッファYサイズ

public:
	DirectXGraphics() {};
	~DirectXGraphics() { Uninit(); };

	static DirectXGraphics* Instance();

	bool Init(HWND hWnd, UINT in_ScreenWidth, UINT in_ScreenHeight, bool FullScreen);
	void Uninit();

public:
	ID3D11Device* GetDevice() const;
	ID3D11DeviceContext* GetDeviceContext() const;
	IDXGISwapChain* GetSwapChain() const;
	ID3D11RenderTargetView* GetRenderTargetView() const;

};

