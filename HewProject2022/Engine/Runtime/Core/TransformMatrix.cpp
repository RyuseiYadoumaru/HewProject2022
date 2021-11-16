//*****************************************************************************
//!	@file	Engine/Runtime/Core/TransformMatrix.cpp
//!	@brief	
//!	@note	座標変換行列
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "TransformMatrix.h"
#include "../Graphics/Shader.h"
#include "../Tools/Log.h"
#include "../Application.h"
#include "../Graphics/DirectXGraphics.h"

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
TransformMatrix::TransformMatrix()
{
	m_ConstanceBufferWorld = nullptr;
	m_ConstanceBufferView = nullptr;
	m_ConstanceBufferProjection = nullptr;

	m_ConstanceBufferCameraPos = nullptr;

}

//==============================================================================
//!	@fn		Instance
//!	@brief	座標変換行列インスタンス取得
//!	@param	
//!	@retval	インスタンス
//==============================================================================
TransformMatrix* TransformMatrix::Instance()
{
	static TransformMatrix Instance;
	return &Instance;
}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool TransformMatrix::Init()
{
	DirectXGraphics* DirectGraphic = DirectXGraphics::Instance();
	Application* App = Application::Instance();
	ID3D11Device* device = DirectGraphic->GetDevice();
	bool sts = false;

	/****	ワールド座標行列生成	****/
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferMatrixWorld), m_ConstanceBufferWorld.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "ワールド座標行列生成に失敗しました");
		return false;
	}

	/****	ビュー座標行列生成	****/
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferMatrixView), m_ConstanceBufferView.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "ビュー座標行列生成に失敗しました");
		return false;
	}

	/****	プロジェクション座標行列生成	****/
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferMatrixProjection), m_ConstanceBufferProjection.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "プロジェクション座標行列生成に失敗しました");
		return false;
	}

	/****	カメラ座標行列生成	****/
	sts = Shader::CreateConstanceBufferWrite(device, sizeof(ConstanceBufferCameraPos), m_ConstanceBufferCameraPos.GetAddressOf());
	if (sts == false)
	{
		Log::LogError(App->GetHandle(), "カメラ座標生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		SetTransformMatrix
//!	@brief	座標変換行列を定数バッファにセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool TransformMatrix::SetTransformMatrix(TYPE in_Type, XMFLOAT4X4& in_Matrix)
{
	ALIGN16 XMMATRIX mtx;
	mtx = DirectX::XMLoadFloat4x4(&in_Matrix);

	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE Date;
	HRESULT hr;
	bool sts = false;

	switch (in_Type)
	{
		/****	ワールド座標行列	****/
	case TYPE::WORLD:
		m_World.Matrix = DirectX::XMMatrixTranspose(mtx);
		hr = deviceContext->Map(m_ConstanceBufferWorld.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Date);
		if (SUCCEEDED(hr))
		{
			memcpy_s(Date.pData, Date.RowPitch, &mtx, sizeof(ConstanceBufferMatrixWorld));

			deviceContext->Unmap(m_ConstanceBufferWorld.Get(), 0);
			sts = true;
		}
		deviceContext->VSSetConstantBuffers(1, 1, m_ConstanceBufferWorld.GetAddressOf());
		deviceContext->PSSetConstantBuffers(1, 1, m_ConstanceBufferWorld.GetAddressOf());

		break;

		/****	ビュー座標行列	****/
	case TYPE::VIEW:
		m_View.Matrix = DirectX::XMMatrixTranspose(mtx);
		hr = deviceContext->Map(m_ConstanceBufferView.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Date);
		if (SUCCEEDED(hr))
		{
			memcpy_s(Date.pData, Date.RowPitch, &mtx, sizeof(ConstanceBufferMatrixView));

			deviceContext->Unmap(m_ConstanceBufferView.Get(), 0);
			sts = true;
		}
		deviceContext->VSSetConstantBuffers(2, 1, m_ConstanceBufferView.GetAddressOf());
		deviceContext->PSSetConstantBuffers(2, 1, m_ConstanceBufferView.GetAddressOf());

		break;

		/****	プロジェクション座標行列	****/
	case TYPE::PROJECTION:
		m_Projection.Matrix = DirectX::XMMatrixTranspose(mtx);
		hr = deviceContext->Map(m_ConstanceBufferProjection.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Date);
		if (SUCCEEDED(hr))
		{
			memcpy_s(Date.pData, Date.RowPitch, &mtx, sizeof(ConstanceBufferMatrixProjection));

			deviceContext->Unmap(m_ConstanceBufferProjection.Get(), 0);
			sts = true;
		}
		deviceContext->VSSetConstantBuffers(3, 1, m_ConstanceBufferProjection.GetAddressOf());
		deviceContext->PSSetConstantBuffers(3, 1, m_ConstanceBufferProjection.GetAddressOf());

		break;
	}

	return sts;
}

//==============================================================================
//!	@fn		SetCameraPosition
//!	@brief	カメラ座標を定数バッファにセット
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool TransformMatrix::SetCameraPosition(XMFLOAT3& in_Position)
{
	HRESULT hr;
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();
	D3D11_MAPPED_SUBRESOURCE Date;
	bool sts = false;

	m_Camera.CameraPos[0] = in_Position.x;
	m_Camera.CameraPos[1] = in_Position.y;
	m_Camera.CameraPos[2] = in_Position.z;
	m_Camera.CameraPos[3] = 0.0f;

	hr = deviceContext->Map(m_ConstanceBufferCameraPos.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Date);
	if (SUCCEEDED(hr))
	{
		memcpy_s(Date.pData, Date.RowPitch, &m_Camera, sizeof(ConstanceBufferCameraPos));

		deviceContext->Unmap(m_ConstanceBufferCameraPos.Get(), 0);
		sts = true;
	}
	deviceContext->VSSetConstantBuffers(4, 1, m_ConstanceBufferCameraPos.GetAddressOf());
	deviceContext->PSSetConstantBuffers(4, 1, m_ConstanceBufferCameraPos.GetAddressOf());
	return true;
}
