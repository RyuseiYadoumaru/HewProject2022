//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/DirectXGraphics.h
//!	@brief	
//!	@note	DirectX�O���t�B�b�N�Ɋւ��鏈��
//!	@author	YadoumaruRyusei
//*****************************************************************************

#pragma once
#include <d3d11.h>
#include	<wrl/client.h>

using Microsoft::WRL::ComPtr;

class DirectXGraphics
{
private:
	ComPtr<ID3D11Device>			D3d11Device;		//Direct3D�f�o�C�X
	ComPtr<ID3D11DeviceContext>		ImmediateContext;	//Direct3D�f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>			SwapChain;			//�X���b�v�`�F�C��
	ComPtr<ID3D11RenderTargetView>	RenderTargetView;	//�����_�[�^�[�Q�b�g�r���[

	ComPtr<ID3D11Texture2D>			DepthStencilTexture;//Z�o�b�t�@�A�X�e���V���o�b�t�@
	ComPtr<ID3D11DepthStencilView>	DepthStencilView;	//Z�o�b�t�@�A�X�e���V���r���[

	ComPtr<ID3D11BlendState>		BlendAlphaEnable;	//�u�����h���

	D3D_DRIVER_TYPE					DriverType;			//�h���C�o�^�C�v
	D3D_FEATURE_LEVEL				FeatureLevel;		//�@�\���x��

	UINT							ScreenWidth;		//�o�b�N�o�b�t�@X�T�C�Y
	UINT							ScreenHeight;		//�o�b�N�o�b�t�@Y�T�C�Y

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

