//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 g_mtxWVP;
float4x4 g_mtxWIT;
float4x4 g_mtxWI;
float4x4 g_mtxW;

float4x4 g_mtxLightWVP;
float g_lightFar;
texture g_depthTex;
float g_depthEpsilon;

float3 g_posEyeW;
float3 g_lightDirW;
float4 g_diffColor;

texture g_texture;
float g_contourScl;

texture g_animeDrawTex;

//------------------------------------------------
// テクスチャサンプラ
//------------------------------------------------
sampler TextureSampler		=	sampler_state { Texture = <g_texture>; };
sampler TextureSamplerAnime	=	sampler_state { Texture = <g_animeDrawTex>; };
sampler TextureSamplerDepth	=	sampler_state { Texture = <g_depthTex>; };

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void mainVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	float2 in_uv : TEXCOORD0,
	out float4 out_posH : POSITION,
	out float2 out_uv : TEXCOORD0,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// UV
	out_uv = in_uv;

	// ライトから見る座標変換
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ライトから見る深度値変換
	//out_depthWV = mul(float4(in_pos, 1.0f), g_mtxLightWVP).z / g_lightFar;
	// lightPosH.z / farと計算が一緒のため要らない
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void mainPS(float2 in_uv : TEXCOORD0,
	float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
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
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// 影の処理 /////
	// テクスチャ座標の算出
	in_lightPosH.xyz /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// 深度値の対比
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).x + g_depthEpsilon) < in_lightPosH.z ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}

//------------------------------------------------
// テクスチャなし頂点シェーダ
//------------------------------------------------
void mainVS_noTex(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// ライトから見る座標変換
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ライトから見る深度値変換
	out_depthWV = out_lightPosH.z / out_lightPosH.w;
}

//------------------------------------------------
// テクスチャなしシェーダ
//------------------------------------------------
void mainPS_noTex(float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
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
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// 影の処理 /////
	// テクスチャ座標の算出
	in_lightPosH.xyz /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// 深度値の対比
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).x + g_depthEpsilon) < in_lightPosH.z ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}


//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void shadowVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	float2 in_uv : TEXCOORD0,
	out float4 out_posH : POSITION,
	out float2 out_uv : TEXCOORD0,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// UV
	out_uv = in_uv;

	// ライトから見る座標変換
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ライトから見る深度値変換
	out_depthWV = out_lightPosH.z / g_lightFar;
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void shadowPS(float2 in_uv : TEXCOORD0,
	float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	float  in_depthWV : TEXCOORD4,
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
	float4 diffuse = tex2D(TextureSampler, in_uv) * g_diffColor * tex2D(TextureSamplerAnime, float2(diff, 0.1f));

	// 色の出力
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// 影の処理 /////
	// テクスチャ座標の算出
	in_lightPosH.xy /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// 深度値の対比
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).r + g_depthEpsilon) > in_depthWV ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}

//------------------------------------------------
// テクスチャなし頂点シェーダ
//------------------------------------------------
void shadowVS_noTex(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// ライトから見る座標変換
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ライトから見る深度値変換
	out_depthWV = out_lightPosH.z / g_lightFar;
}

//------------------------------------------------
// テクスチャなしシェーダ
//------------------------------------------------
void shadowPS_noTex(float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	float  in_depthWV : TEXCOORD4,
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
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// 影の処理 /////
	// テクスチャ座標の算出
	in_lightPosH.xy /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// 深度値の対比
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).r + g_depthEpsilon) > in_depthWV ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
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
// ステンシルシャドウ頂点シェーダ
//------------------------------------------------
void stencilShadowVS(
	float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION)
{
	// 法線
	in_normal = normalize(in_normal);
	float3 normalW = normalize(mul(float4(in_normal, 0.0f), g_mtxW).xyz);
	float3 lightDirL = normalize(mul(float4(g_lightDirW, 0.0f), g_mtxWI).xyz);

	// 法線とライトの向きチェック
	float edge = dot(normalW, -lightDirL);

	// 反対側のみ伸ばす
	if (edge < 0.0f)
	{
		// 変換後座標
		out_posH = mul(float4(in_pos + (lightDirL*1000.0f), 1.0f), g_mtxWVP);
	}
	else
	{
		// 変換後座標
		out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);
	}
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
	pass P3
	{
		vertexShader = compile vs_3_0 stencilShadowVS();
	}
	pass P4
	{
		vertexShader = compile vs_3_0 shadowVS();
		pixelShader = compile ps_3_0 shadowPS();
	}
	pass P5
	{
		vertexShader = compile vs_3_0 shadowVS_noTex();
		pixelShader = compile ps_3_0 shadowPS_noTex();
	}
}
