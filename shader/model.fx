//------------------------------------------------
// グローバル変数
//------------------------------------------------
float4x4 g_mtxWVP;

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
				float2 in_uv:TEXCOORD0,
 				out float4 out_posH : POSITION,
 				out float2 out_uv :TEXCOORD0)
{
	// 変換後座標
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// UV
	out_uv = in_uv;
}

//------------------------------------------------
// ピクセルシェーダ
//------------------------------------------------
void mainPS(	float2 in_uv : TEXCOORD0,
				out float4 out_color : COLOR0)
{
	// 色の出力
	out_color = tex2D(TextureSampler, in_uv);
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
