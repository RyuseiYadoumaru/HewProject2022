//*****************************************************************************
//!	@file	Engine/Runtime/Graphics/DirectXGraphics.cpp
//!	@brief	
//!	@note	DirectX�O���t�B�b�N�Ɋւ��鏈��
//!	@author	YadoumaruRyusei
//*****************************************************************************


#include "DirectXGraphics.h"
#include "../../../directxtex/include/WICTextureLoader.h"
#include <locale.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")	

//==============================================================================
//!	@fn		Instance
//!	@brief	�C���X�^���X�擾
//!	@param	
//!	@retval	�C���X�^���X
//==============================================================================
DirectXGraphics* DirectXGraphics::Instance()
{
	static DirectXGraphics Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	������
//!	@param	�E�B���h�E�n���h��
//!	@param	�o�b�N�o�b�t�@X�T�C�Y
//!	@param	�o�b�N�o�b�t�@Y�T�C�Y
//!	@param	FullScreen�t���O
//!	@retval	true:����I���@false:�ُ�I��
//==============================================================================
bool DirectXGraphics::Init(HWND hWnd, UINT in_ScreenWidth, UINT in_ScreenHeight, bool FullScreen)
{
	HRESULT	hr = S_OK;
	IDXGIFactory* factory;				// factory
	IDXGIAdapter* adapter;				// videocard
	IDXGIOutput* adapterOutput;			// monitor
	unsigned int numModes;
	unsigned int numerator = 60;		// ���q
	unsigned int denominator = 1;		// ����
	DXGI_MODE_DESC* displayModeList;

	/****	�X�N���[���T�C�Y�ݒ�	****/
	ScreenWidth = in_ScreenWidth;
	ScreenHeight = in_ScreenHeight;

	/****	�h���C�o�̎��	****/
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

	/****	�@�\���x��	****/
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,					// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,					// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1					// Direct9.1�Ή�GPU���x��
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

	/****	�X���b�v�`�F�C���ݒ�	****/
	// �X���b�v�`�F�C���Ƃ́A�E�C���h�E�ւ̕\���_�u���o�b�t�@���Ǘ�����
	// �N���X�@�}���`�T���v�����O�A���t���b�V�����[�g���ݒ�ł���
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));					// �[���N���A
	sd.BufferCount = 1;								// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = ScreenWidth;				// �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = ScreenHeight;			// �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B �͈͂O�D�O����P�D�O)
	sd.BufferDesc.RefreshRate.Numerator = numerator;		// ���t���b�V�����[�g�i����j
	sd.BufferDesc.RefreshRate.Denominator = denominator;	// ���t���b�V�����[�g�i���q�j
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �o�b�N�o�b�t�@�̎g�p���@
	sd.OutputWindow = hWnd;			// �֘A�t����E�C���h�E
	sd.SampleDesc.Count = 1;		// �}���`�T���v���̐�
	sd.SampleDesc.Quality = 0;		// �}���`�T���v���̃N�I���e�B
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	/****	�E�B���h�E���[�h�E�t���X�N���[�����[�h�ؑ�	****/
	if (FullScreen == true)
	{
		sd.Windowed = FALSE;	// �E�C���h�E���[�h
	}
	else
	{
		sd.Windowed = TRUE;		// �E�C���h�E���[�h
	}

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// ���[�h�̎����؂�ւ�

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		DriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain
		(
			NULL,				// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�i�m�t�k�k�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
			DriverType,			// �f�o�C�X�h���C�o�̃^�C�v
			NULL,				// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
			createDeviceFlags,	// �f�o�C�X�t���O
			featureLevels,		// �@�\���x��
			numFeatureLevels,	// �@�\���x����
			D3D11_SDK_VERSION,	// 
			&sd,				// �X���b�v�`�F�C���̐ݒ�
			&SwapChain,			// IDXGIDwapChain�C���^�t�F�[�X	
			&D3d11Device,		// ID3D11Device�C���^�t�F�[�X
			&FeatureLevel,		// �T�|�[�g����Ă���@�\���x��
			&ImmediateContext	// �f�o�C�X�R���e�L�X�g
		);
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr))
	{
		return false;
	}

	/****	�o�b�N�o�b�t�@�֌W�ݒ�	****/
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	//�����_�����O�^�[�Q�b�g�쐬
	hr = D3d11Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView);
	pBackBuffer->Release();
	pBackBuffer = NULL;
	if (FAILED(hr))
	{
		return false;
	}

	/****	�[�x�X�e���V���o�b�t�@�쐬	****/
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

	/****	�����_�����O�^�[�Q�b�g�ݒ�	****/
	//2D�Ȃ̂�Z�o�b�t�@�����ɐݒ�
	ImmediateContext->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), NULL);

	/****	�r���[�|�[�g�ݒ�	****/
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)ScreenWidth;
	viewport.Height = (FLOAT)ScreenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	ImmediateContext->RSSetViewports(1, &viewport);

	/****	�u�����h�X�e�[�g�ݒ�	****/
	D3D11_BLEND_DESC BlendDesc;

	// �e�N�X�`�����ߏ������s����悤�ɐݒ�
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
//!	@brief	�I������
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
//!	@brief	D3d11�f�o�C�X�擾
//!	@param	
//!	@retval	Device
//==============================================================================
ID3D11Device* DirectXGraphics::GetDevice() const
{

	return D3d11Device.Get();
}

//==============================================================================
//!	@fn		GetDeviceContext
//!	@brief	D3d11�f�o�C�X�R���e�L�X�g�擾
//!	@param	
//!	@retval	ImmediateContext
//==============================================================================
ID3D11DeviceContext* DirectXGraphics::GetDeviceContext() const
{
	return ImmediateContext.Get();
}

//==============================================================================
//!	@fn		GetSwapChain
//!	@brief	�X���b�v�`�F�C���擾
//!	@param	
//!	@retval	SwapChain
//==============================================================================
IDXGISwapChain* DirectXGraphics::GetSwapChain() const
{
	return SwapChain.Get();
}

//==============================================================================
//!	@fn		GetRenderTargetView
//!	@brief	�����_�����O�^�[�Q�b�g�擾
//!	@param	
//!	@retval	RenderTargetView
//==============================================================================
ID3D11RenderTargetView* DirectXGraphics::GetRenderTargetView() const
{
	return RenderTargetView.Get();
}
