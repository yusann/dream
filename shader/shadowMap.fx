//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 g_mtxLightWVP;
float4x4 g_mtxLightWV;
float g_far;

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void mainVS(float3 in_posL : POSITION,
	out float4 out_posH : POSITION,
	out float out_depthWV : TEXCOORD0)
{
	// 変換後座標
	out_posH = mul(float4(in_posL, 1.0f), g_mtxLightWVP);

	// 深度値
	out_depthWV = mul(float4(in_posL, 1.0f), g_mtxLightWV).z / g_far;
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void mainPS(float in_depthWV : TEXCOORD0,
	out float4 out_color : COLOR0)
{
	out_color = in_depthWV;
}

//------------------------------------------------
// テクニック宣言
//------------------------------------------------
technique BasicTech
{
	pass P0
	{
		vertexShader = compile vs_3_0 mainVS();
		pixelShader = compile ps_3_0 mainPS();
	}
}
