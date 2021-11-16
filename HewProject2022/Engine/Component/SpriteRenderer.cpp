//*****************************************************************************
//!	@file	Engine/Component/SpriteRenderer.cpp
//!	@brief	
//!	@note	2Dグラフィックスのスプライトをレンダリング
//!	@author	YadoumaruRyusei
//*****************************************************************************

#include "SpriteRenderer.h"
#include "../Runtime/Graphics/Shader.h"
#include "../Runtime/Tools/Log.h"
#include "../Runtime/Core/TransformMatrix.h"
#include "../Data/DataArray.h"


//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
const UINT GameEngine::SpriteRenderer::VERTEX_NUM = 4;	//頂点数

//==============================================================================
//!	@fn		Constructor
//!	@brief	コンストラクタ
//!	@param	
//==============================================================================
GameEngine::SpriteRenderer::SpriteRenderer(XMFLOAT4X4* in_WorldMatrix) : Renderer()
{
	SpriteName = "Default";
	VertexShaderName = "vs_2DSprite";
	PixcelShaderName = "ps_2DSprite";
	WorldMatrix = in_WorldMatrix;

}

//==============================================================================
//!	@fn		Init
//!	@brief　初期化
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SpriteRenderer::Init()
{
	bool sts = false;

	/****	デバイス取得	****/
	ID3D11Device* device = DirectXGraphics::Instance()->GetDevice();

	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	頂点シェーダー生成	****/
	vertexShader.Set(DataArray::GetvsShader(VertexShaderName));

	/****	ピクセルシェーダー生成	****/
	pixcelShader.Set(DataArray::GetpsShader(PixcelShaderName));

	/****	SRV生成		****/
	sprite.Set(DataArray::GetSpriteData(SpriteName));

	Rect.Set(sprite.GetSize().x, sprite.GetSize().y);

	/****	頂点座標	****/
	VERTEX vertex[VERTEX_NUM] =
	{
		XMFLOAT3(Rect.GetButtomLeft().x, Rect.GetButtomLeft().y, 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(0.0f,1.0f),
		XMFLOAT3(Rect.GetTopLeft().x,	 Rect.GetTopLeft().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(0.0f,0.0f),
		XMFLOAT3(Rect.GetButtomRight().x,Rect.GetButtomRight().y,0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(1.0f,1.0f),
		XMFLOAT3(Rect.GetTopRight().x,	 Rect.GetTopRight().y,	 0.0f),	XMFLOAT4(Color.r,Color.g,Color.b,Color.a),	XMFLOAT2(1.0f,0.0f)

	};

	/****	頂点バッファ生成	****/
	sts = Shader::CreateVertexBuffer
	(
		device,
		sizeof(VERTEX),
		VERTEX_NUM,
		vertex,
		&VertexBuffer
	);
	if (sts == false)
	{
		Log::LogError("頂点バッファの生成に失敗しました");
		return false;
	}

	return true;
}

//==============================================================================
//!	@fn		Render
//!	@brief　描画
//!	@param	
//!	@retval	true:正常終了　false:異常終了
//==============================================================================
bool GameEngine::SpriteRenderer::Render()
{
	/****	デバイスコンテキスト取得	****/
	ID3D11DeviceContext* deviceContext = DirectXGraphics::Instance()->GetDeviceContext();

	/****	行列変換生成	****/
	TransformMatrix* TransformMtx = TransformMatrix::Instance();

	/****	頂点バッファ設定	****/
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	bool sts = false;

	/****	ワールド座標行列セット	****/
	sts = TransformMtx->SetTransformMatrix(TransformMatrix::TYPE::WORLD, *WorldMatrix);
	if (sts == false)
	{
		Log::LogError("ワールド座標行列のセットに失敗しました。");
		return false;
	}


	/****	頂点バッファセット	****/
	deviceContext->IASetVertexBuffers(
		0,						// スタートスロット
		1,						// 頂点バッファ個数
		&VertexBuffer,			// 頂点バッファの先頭アドレス
		&stride,				// ストライド
		&offset);				// オフセット


	/****	トポロジーセット	****/
	deviceContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP));


	/****	頂点レイアウトセット	****/
	DataArray* daa = DataArray::Instance();
	deviceContext->IASetInputLayout(vertexShader.GetInputLayout());

	deviceContext->VSSetShader(vertexShader.GetVertexShader(), nullptr, 0);		// 頂点シェーダーをセット
	deviceContext->PSSetShader(pixcelShader.GetPixelShader(), nullptr, 0);		// ピクセルシェーダーをセット

	/****	SRVセット	****/
	deviceContext->PSSetShaderResources(0, 1, sprite.GetShaderResourceView());

	/****	描画	****/
	deviceContext->Draw(VERTEX_NUM, 0);

	return true;
}

//==============================================================================
//!	@fn		Release
//!	@brief　解放処理
//!	@param	
//!	@retval	
//==============================================================================
void GameEngine::SpriteRenderer::Release()
{
	if (VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
}