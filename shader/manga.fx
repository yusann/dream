//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 g_mtxWVP;
float4x4 g_mtxWIT;
float4x4 g_mtxWI;
float4x4 g_mtxW;

float4x4 g_mtxLightWVP;
float g_lightFar;
texture g_depthTex;
float g_depthEpsilon;

float3 g_posEyeW;
float3 g_lightDirW;
float4 g_diffColor;

texture g_texture;
float g_contourScl;

texture g_animeDrawTex;

//------------------------------------------------
// �e�N�X�`���T���v��
//------------------------------------------------
sampler TextureSampler		=	sampler_state { Texture = <g_texture>; };
sampler TextureSamplerAnime	=	sampler_state { Texture = <g_animeDrawTex>; };
sampler TextureSamplerDepth	=	sampler_state { Texture = <g_depthTex>; };

//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void mainVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	float2 in_uv : TEXCOORD0,
	out float4 out_posH : POSITION,
	out float2 out_uv : TEXCOORD0,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ���[���h���W
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// �@��
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// UV
	out_uv = in_uv;

	// ���C�g���猩����W�ϊ�
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ���C�g���猩��[�x�l�ϊ�
	//out_depthWV = mul(float4(in_pos, 1.0f), g_mtxLightWVP).z / g_lightFar;
	// lightPosH.z / far�ƌv�Z���ꏏ�̂��ߗv��Ȃ�
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void mainPS(float2 in_uv : TEXCOORD0,
	float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	out float4 out_color : COLOR0)
{
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// �f�B�t���[�Y
	float diff = dot(in_normalW, -g_lightDirW)*0.5f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// �������C�g�i���j
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// �f�B�t���[�Y�Z�b�g�i���s�����j
	float4 diffuse = tex2D(TextureSampler, in_uv) * g_diffColor * tex2D(TextureSamplerAnime, float2(diff,0.1f));

	// �F�̏o��
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// �e�̏��� /////
	// �e�N�X�`�����W�̎Z�o
	in_lightPosH.xyz /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// �[�x�l�̑Δ�
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).x + g_depthEpsilon) < in_lightPosH.z ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}

//------------------------------------------------
// �e�N�X�`���Ȃ����_�V�F�[�_
//------------------------------------------------
void mainVS_noTex(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ���[���h���W
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// �@��
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// ���C�g���猩����W�ϊ�
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ���C�g���猩��[�x�l�ϊ�
	out_depthWV = out_lightPosH.z / out_lightPosH.w;
}

//------------------------------------------------
// �e�N�X�`���Ȃ��V�F�[�_
//------------------------------------------------
void mainPS_noTex(float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	out float4 out_color : COLOR0)
{
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// �f�B�t���[�Y
	float diff = dot(in_normalW, -g_lightDirW)*0.4f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// �������C�g�i���j
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// �f�B�t���[�Y�Z�b�g�i���s�����j
	float4 diffuse = g_diffColor * tex2D(TextureSamplerAnime, float2(diff, 0.5f));

	// �F�̏o��
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// �e�̏��� /////
	// �e�N�X�`�����W�̎Z�o
	in_lightPosH.xyz /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// �[�x�l�̑Δ�
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).x + g_depthEpsilon) < in_lightPosH.z ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}


//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void shadowVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	float2 in_uv : TEXCOORD0,
	out float4 out_posH : POSITION,
	out float2 out_uv : TEXCOORD0,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ���[���h���W
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// �@��
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// UV
	out_uv = in_uv;

	// ���C�g���猩����W�ϊ�
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ���C�g���猩��[�x�l�ϊ�
	out_depthWV = out_lightPosH.z / g_lightFar;
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void shadowPS(float2 in_uv : TEXCOORD0,
	float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	float  in_depthWV : TEXCOORD4,
	out float4 out_color : COLOR0)
{
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// �f�B�t���[�Y
	float diff = dot(in_normalW, -g_lightDirW)*0.5f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// �������C�g�i���j
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// �f�B�t���[�Y�Z�b�g�i���s�����j
	float4 diffuse = tex2D(TextureSampler, in_uv) * g_diffColor * tex2D(TextureSamplerAnime, float2(diff, 0.1f));

	// �F�̏o��
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// �e�̏��� /////
	// �e�N�X�`�����W�̎Z�o
	in_lightPosH.xy /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// �[�x�l�̑Δ�
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).r + g_depthEpsilon) > in_depthWV ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}

//------------------------------------------------
// �e�N�X�`���Ȃ����_�V�F�[�_
//------------------------------------------------
void shadowVS_noTex(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION,
	out float3 out_normal : TEXCOORD1,
	out float3 out_posW : TEXCOORD2,
	out float4 out_lightPosH : TEXCOORD3,
	out float  out_depthWV : TEXCOORD4)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);

	// ���[���h���W
	out_posW = mul(float4(in_pos, 1.0f), g_mtxW).xyz;

	// �@��
	out_normal = normalize(mul(float4(in_normal, 0.0f), g_mtxWIT).xyz);

	// ���C�g���猩����W�ϊ�
	out_lightPosH = mul(float4(in_pos, 1.0f), g_mtxLightWVP);

	// ���C�g���猩��[�x�l�ϊ�
	out_depthWV = out_lightPosH.z / g_lightFar;
}

//------------------------------------------------
// �e�N�X�`���Ȃ��V�F�[�_
//------------------------------------------------
void shadowPS_noTex(float3 in_normalW : TEXCOORD1,
	float3 in_posW : TEXCOORD2,
	float4 in_lightPosH : TEXCOORD3,
	float  in_depthWV : TEXCOORD4,
	out float4 out_color : COLOR0)
{
	// �@��
	in_normalW = normalize(in_normalW);

	// �J�����܂ł̃x�N�g��
	float3 toEyeW = normalize(g_posEyeW - in_posW);

	// �f�B�t���[�Y
	float diff = dot(in_normalW, -g_lightDirW)*0.4f + 0.5f;

	float rim = 1.0f - abs(dot(toEyeW, in_normalW))*1.2f;

	// �������C�g�i���j
	float3 lightColor = float3(0.2f, 0.2f, 0.2f);
	float4 rimlight = float4(lightColor * rim, 0.0f);

	//// �f�B�t���[�Y�Z�b�g�i���s�����j
	float4 diffuse = g_diffColor * tex2D(TextureSamplerAnime, float2(diff, 0.5f));

	// �F�̏o��
	float4 color;
	color = diffuse + rimlight;
	color.w = 1.0f;

	// �e�̏��� /////
	// �e�N�X�`�����W�̎Z�o
	in_lightPosH.xy /= in_lightPosH.w;
	in_lightPosH.x = in_lightPosH.x * 0.5f + 0.5f;
	in_lightPosH.y = in_lightPosH.y * -0.5f + 0.5f;

	// �[�x�l�̑Δ�
	float s = (tex2D(TextureSamplerDepth, in_lightPosH.xy).r + g_depthEpsilon) > in_depthWV ? 0.2f : 1.0f;
	out_color = float4(color.rgb * s, color.a);
}

//------------------------------------------------
// �֊s���_�V�F�[�_
//------------------------------------------------
void contourVS(float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION)
{
	// �ϊ�����W
	out_posH = mul(float4(in_pos + (in_normal*g_contourScl), 1.0f), g_mtxWVP);
}

//------------------------------------------------
// �֊s�V�F�[�_
//------------------------------------------------
void contourPS( out float4 out_color : COLOR0 )
{
	// �F�̏o��
	out_color = float4(0.1f,0.1f,0.1f,1.0f);
}

//------------------------------------------------
// �X�e���V���V���h�E���_�V�F�[�_
//------------------------------------------------
void stencilShadowVS(
	float3 in_pos : POSITION,
	float3 in_normal : NORMAL0,
	out float4 out_posH : POSITION)
{
	// �@��
	in_normal = normalize(in_normal);
	float3 normalW = normalize(mul(float4(in_normal, 0.0f), g_mtxW).xyz);
	float3 lightDirL = normalize(mul(float4(g_lightDirW, 0.0f), g_mtxWI).xyz);

	// �@���ƃ��C�g�̌����`�F�b�N
	float edge = dot(normalW, -lightDirL);

	// ���Α��̂ݐL�΂�
	if (edge < 0.0f)
	{
		// �ϊ�����W
		out_posH = mul(float4(in_pos + (lightDirL*1000.0f), 1.0f), g_mtxWVP);
	}
	else
	{
		// �ϊ�����W
		out_posH = mul(float4(in_pos, 1.0f), g_mtxWVP);
	}
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
	pass P1
	{
		vertexShader = compile vs_3_0 mainVS_noTex();
		pixelShader = compile ps_3_0 mainPS_noTex();
	}
	pass P2
	{
		vertexShader = compile vs_3_0 contourVS();
		pixelShader = compile ps_3_0 contourPS();
	}
	pass P3
	{
		vertexShader = compile vs_3_0 stencilShadowVS();
	}
	pass P4
	{
		vertexShader = compile vs_3_0 shadowVS();
		pixelShader = compile ps_3_0 shadowPS();
	}
	pass P5
	{
		vertexShader = compile vs_3_0 shadowVS_noTex();
		pixelShader = compile ps_3_0 shadowPS_noTex();
	}
}
