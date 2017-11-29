sampler tex;
float3 posEyeW;
float3 toEyeW;
float3 lightDirW;
float  specularPower;
float  specularColor;

float4 main(float4 in_color   : COLOR0,
			float2 in_uv      : TEXCOORD0,
			float3 in_normalW : TEXCOORD1,
			float3 in_posW    : TEXCOORD2) : COLOR0
{
	// 法線
	in_normalW = normalize(in_normalW);

	// カメラまでのベクトル
	float3 toEyeW = normalize(posEyeW - in_posW);

	// 反射ベクトル
	float3 r = reflect(lightDirW, in_normalW);

	// スペキュラーパワー
	float spec = pow(max(dot(r, toEyeW), 0.0f), specularPower);

	// ディフューズ
	//float diff = max(dot(in_normalW, -lightDirW), 0.2f);
	float diff = max(dot(in_normalW, -lightDirW)*0.5f+0.5f,0.2f);
	diff = min(diff, 1.0f);

	float rim = abs(dot(toEyeW, in_normalW))*1.8f;
	

	// スペキュラーセット（反射光＝ボーリングの光とか）
	float3 specular = (specularColor, specularColor, specularColor) * spec;

	// ディフューズセット（平行光源）
	float3 diffuse  = (diff, diff, diff);

	// アンビエント（発光）
	float3 ambient = (0.2f, 0.2f, 0.2f);

	// リムライト（縁）
	float4 rimlight = (rim, rim, rim,1.0f);

	return float4(specular + diffuse + ambient, 1.0f) * tex2D(tex, in_uv) * in_color;
}