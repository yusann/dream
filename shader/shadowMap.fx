//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 g_mtxLightWVP;
float4x4 g_mtxLightWV;
float g_far;

//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void mainVS(float3 in_posL : POSITION,
	out float4 out_posH : POSITION,
	out float2 out_depth : TEXCOORD0)
{
	// �ϊ�����W
	out_posH = mul(float4(in_posL, 1.0f), g_mtxLightWVP);

	// �[�x�l
	out_depth = out_posH.zw;
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void mainPS(float2 in_depthWV : TEXCOORD0,
	out float4 out_color : COLOR0)
{
	out_color = in_depthWV.x/ in_depthWV.y;
}

//------------------------------------------------
// �e�N�j�b�N�錾
//------------------------------------------------
technique BasicTech
{
	pass P0
	{
		vertexShader = compile vs_3_0 mainVS();
		pixelShader = compile ps_3_0 mainPS();
	}
}
