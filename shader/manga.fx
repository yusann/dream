//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 g_mtxWVP;
float4x4 g_mtxWIT;
float4x4 g_mtxW;

float3 g_posEyeW;
float3 g_lightDirW;
float4 g_diffColor;

texture g_texture;
float g_contourScl;

texture g_animeDrawTex;

//------------------------------------------------
// テクスチャサンプラ
//------------------------------------------------
sampler TextureSampler =
sampler_state
{
	Texture = <g_texture>;
};
sampler TextureSamplerAnime =
sampler_state
{
	Texture = <g_animeDrawTex>;
};

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void mainVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	float2 in_uv : TEXCOORD0,
	out float4 out_posH : POSITION,
	out float2 out_uv : TEXCOORD0,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// UV
	out_uv = in_uv;
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void mainPS(float2 in_uv : TEXCOORD0,
	float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	out float4 out_color : COLOR0)
{
	// 法線
	in_normalW = normalize(in_normalW);

	// カメラまでのベクトル
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// ディフューズ
	float diff = dot(in_normalW, -g_lightDirW)*0.5f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// リムライト（縁）
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// ディフューズセット（平行光源）
	float4 diffuse = tex2D(TextureSampler, in_uv) * g_diffColor * tex2D(TextureSamplerAnime, float2(diff,0.1f));

	// 色の出力
	out_color = diffuse + rimlight;
	out_color.w = 1.0f;
}

//------------------------------------------------
// テクスチャなし頂点シェーダ
//------------------------------------------------
void mainVS_noTex(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);
}

//------------------------------------------------
// テクスチャなしシェーダ
//------------------------------------------------
void mainPS_noTex(float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	out float4 out_color : COLOR0)
{
	// 法線
	in_normalW = normalize(in_normalW);

	// カメラまでのベクトル
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// ディフューズ
	float diff = dot(in_normalW, -g_lightDirW)*0.4f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// リムライト（縁）
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// ディフューズセット（平行光源）
	float4 diffuse = g_diffColor * tex2D(TextureSamplerAnime, float2(diff, 0.5f));

	// 色の出力
	out_color = diffuse + rimlight;
	out_color.w = 1.0f;
}

//------------------------------------------------
// 輪郭頂点シェーダ
//------------------------------------------------
void contourVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION)
{
	// 変換後座標
	out_posH = mul(float4(in_pos + (in_normal*g_contourScl), 1.0f), g_mtxWVP);
}

//------------------------------------------------
// 輪郭シェーダ
//------------------------------------------------
void contourPS( out float4 out_color : COLOR0 )
{
	// 色の出力
	out_color = float4(0.1f,0.1f,0.1f,1.0f);
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
	pass P1
	{
		vertexShader = compile vs_3_0 mainVS_noTex();
		pixelShader = compile ps_3_0 mainPS_noTex();
	}
	pass P2
	{
		vertexShader = compile vs_3_0 contourVS();
		pixelShader = compile ps_3_0 contourPS();
	}
}
