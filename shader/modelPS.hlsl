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
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(posEyeW - in_posW);

	// ���˃x�N�g��
	float3 r = reflect(lightDirW, in_normalW);

	// �X�y�L�����[�p���[
	float spec = pow(max(dot(r, toEyeW), 0.0f), specularPower);

	// �f�B�t���[�Y
	//float diff = max(dot(in_normalW, -lightDirW), 0.2f);
	float diff = max(dot(in_normalW, -lightDirW)*0.5f+0.5f,0.2f);
	diff = min(diff, 1.0f);

	float rim = abs(dot(toEyeW, in_normalW))*1.8f;
	

	// �X�y�L�����[�Z�b�g�i���ˌ����{�[�����O�̌��Ƃ��j
	float3 specular = (specularColor, specularColor, specularColor) * spec;

	// �f�B�t���[�Y�Z�b�g�i���s�����j
	float3 diffuse  = (diff, diff, diff);

	// �A���r�G���g�i�����j
	float3 ambient = (0.2f, 0.2f, 0.2f);

	// �������C�g�i���j
	float4 rimlight = (rim, rim, rim,1.0f);

	return float4(specular + diffuse + ambient, 1.0f) * tex2D(tex, in_uv) * in_color;
}