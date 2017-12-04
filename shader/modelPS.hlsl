sampler tex;
float3 posEyeW;
float3 lightDirW;
float  specularPower;
float4 diffColor;

float4 main(float2 in_uv      : TEXCOORD0,
			float3 in_normalW : TEXCOORD1,
			float3 in_posW    : TEXCOORD2) : COLOR0
{
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(posEyeW - in_posW);

	// ���˃x�N�g��
	float3 r = reflect(lightDirW, in_normalW);

	// �X�y�L�����[�p���[
	float spec = pow(max(dot(r, toEyeW), 0.0f), specularPower);

	// �f�B�t���[�Y
	float diff = min(dot(in_normalW, -lightDirW)*0.5f + 0.5f, 1.0f);

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;
	
	// �������C�g�i���j
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// �X�y�L�����[�Z�b�g�i���ˌ����{�[�����O�̌��Ƃ��j
	float3 specColor = float3(1.0f, 1.0f, 1.0f);
	float4 specular = float4(specColor* spec, 1.0f);

	//// �f�B�t���[�Y�Z�b�g�i���s�����j
	float4 diffuse = tex2D(tex, in_uv) * diffColor * diff;

	return specular + diffuse + rimlight;
}