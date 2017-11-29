float4x4 mtxWVP;
float4x4 mtxW;
float4 diffColor;

// 入力
struct IN_VERTEX
{
	float3 pos:POSITION0;
	float3 normal:NORMAL0;
	float2 uv:TEXCOORD0;
};

// 出力
struct OUT_VERTEX
{
	float4 posH:POSITION0;
	float4 color:COLOR0;
	float2 uv:TEXCOORD0;
	float3 normal:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

// メイン
OUT_VERTEX main(IN_VERTEX inv)
{
	// 初期化
	OUT_VERTEX ov = (OUT_VERTEX)0;

	// 変換後座標
	ov.posH = mul(float4(inv.pos, 1.0f), mtxWVP);

	// ワールド座標
	ov.posW = mul(float4(inv.pos, 1.0f), mtxW).xyz;

	// 法線
	ov.normal = normalize(mul(float4( inv.normal, 0.0f),mtxW).xyz);

	// UV
	ov.uv = inv.uv;

	// ディフューズカラー
	ov.color = diffColor;
	return ov;
}