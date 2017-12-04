sampler tex;
float3 posEyeW;
float3 lightDirW;
float  specularPower;
float4 diffColor;

float4 main(float2 in_uv      : TEXCOORD0,
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
	float diff = min(dot(in_normalW, -lightDirW)*0.5f + 0.5f, 1.0f);

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;
	
	// リムライト（縁）
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// スペキュラーセット（反射光＝ボーリングの光とか）
	float3 specColor = float3(1.0f, 1.0f, 1.0f);
	float4 specular = float4(specColor* spec, 1.0f);

	//// ディフューズセット（平行光源）
	float4 diffuse = tex2D(tex, in_uv) * diffColor * diff;

	return specular + diffuse + rimlight;
}