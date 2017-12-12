//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 g_mtxWVP;

texture g_texture;

//------------------------------------------------
// �e�N�X�`���T���v��
//------------------------------------------------
sampler TextureSampler = 
sampler_state
{
    Texture = <g_texture>;
};

//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void mainVS( 	float3 in_pos : POSITION,
				float2 in_uv:TEXCOORD0,
 				out float4 out_posH : POSITION,
 				out float2 out_uv :TEXCOORD0)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// UV
	out_uv = in_uv;
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void mainPS(	float2 in_uv : TEXCOORD0,
				out float4 out_color : COLOR0)
{
	// �F�̏o��
	out_color = tex2D(TextureSampler, in_uv);
}
//------------------------------------------------
// �e�N�j�b�N�錾
//------------------------------------------------
technique BasicTech
{
    pass P0
    {
        vertexShader = compile vs_3_0 mainVS();
        pixelShader  = compile ps_3_0 mainPS();
	}
}
