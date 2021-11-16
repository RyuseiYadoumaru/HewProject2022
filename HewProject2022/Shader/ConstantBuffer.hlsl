
/****	ViewportSize	****/
cbuffer ConstantBufferViewport : register(b0)
{
	uint4 ViewportWidth;
	uint4 ViewportHeight;
};

/****	WorldMatrix	****/
cbuffer ConstantBufferWorld : register(b1)
{
	matrix World;
};

/****	ViewMatrix	****/
cbuffer ConstantBufferView : register(b2)
{
	matrix View;
};

/****	ProjectionMatrix	****/
cbuffer ConstantBufferProjection : register(b3)
{
	matrix Projection;
};

/****	CameraTransform	****/
cbuffer ConstantBufferCameraPos : register(b4)
{
	float4 CameraPos;
}
