//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 g_mtxWVP;
float4x4 g_mtxW;

float3 g_posEyeW;
float3 g_lightDirW;
float  g_specularPower;
float4 g_diffColor;

texture g_texture;

//------------------------------------------------
// テクスチャサンプラ
//------------------------------------------------
sampler TextureSampler = 
sampler_state
{
    Texture = <g_texture>;
};

//------------------------------------------------
// 頂点シェーダ
//------------------------------------------------
void mainVS( 	float3 in_pos : POSITION,
				float3 in_normal : NORMAL0,
				float2 in_uv:TEXCOORD0,
 				out float4 out_posH : POSITION,
 				out float2 out_uv :TEXCOORD0,
 				out float3 out_normal:TEXCOORD1,
 				out float3 out_posW : TEXCOORD2)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ワールド座標
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// 法線
	out_normal = normalize(mul(float4( in_normal, 0.0f),g_mtxW).xyz);

	// UV
	out_uv = in_uv;
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void mainPS(	float2 in_uv : TEXCOORD0,
				float3 in_normalW : TEXCOORD1,
				float3 in_posW : TEXCOORD2,
				out float4 out_color : COLOR0)
{	
	// 法線
	in_normalW = normalize(in_normalW);

	// カメラまでのベクトル
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// 反射ベクトル
	float3 r = reflect(g_lightDirW, in_normalW);

	// スペキュラーパワー
	float spec = pow(max(dot(r, toEyeW), 0.0f), g_specularPower);

	// ディフューズ
	float diff = min(dot(in_normalW, -g_lightDirW)*0.5f + 0.5f, 1.0f);

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;
	
	// リムライト（縁）
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// スペキュラーセット（反射光＝ボーリングの光とか）
	float3 specColor = float3(1.0f, 1.0f, 1.0f);
	float4 specular = float4(specColor* spec, 1.0f);

	//// ディフューズセット（平行光源）
	float4 diffuse = tex2D(TextureSampler, in_uv) * g_diffColor * diff;

	// 色の出力
	out_color = specular + diffuse + rimlight;
}

//------------------------------------------------
// テクニック宣言
//------------------------------------------------
technique BasicTech
{
    pass P0
    {
        vertexShader = compile vs_3_0 mainVS();
        pixelShader  = compile ps_3_0 mainPS();
	}
}
