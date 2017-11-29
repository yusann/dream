float4x4 mtxWVP;
float4x4 mtxW;
float4 diffColor;

// ����
struct IN_VERTEX
{
	float3 pos:POSITION0;
	float3 normal:NORMAL0;
	float2 uv:TEXCOORD0;
};

// �o��
struct OUT_VERTEX
{
	float4 posH:POSITION0;
	float4 color:COLOR0;
	float2 uv:TEXCOORD0;
	float3 normal:TEXCOORD1;
	float3 posW:TEXCOORD2;
};

// ���C��
OUT_VERTEX main(IN_VERTEX inv)
{
	// ������
	OUT_VERTEX ov = (OUT_VERTEX)0;

	// �ϊ�����W
	ov.posH = mul(float4(inv.pos, 1.0f), mtxWVP);

	// ���[���h���W
	ov.posW = mul(float4(inv.pos, 1.0f), mtxW).xyz;

	// �@��
	ov.normal = normalize(mul(float4( inv.normal, 0.0f),mtxW).xyz);

	// UV
	ov.uv = inv.uv;

	// �f�B�t���[�Y�J���[
	ov.color = diffColor;
	return ov;
}