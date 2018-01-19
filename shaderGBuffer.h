#ifndef _SHADER_GBUFFER_H_
#define _SHADER_GBUFFER_H_

//*****************************************************************************
//   �V�F�[�_�}���K���̒�`
//*****************************************************************************
class CShaderGBuffer : public CShaderBase
{
public:

	// �f�t�H���g�R���X�g���N�^
	CShaderGBuffer();
	// �f�X�g���N�^
	~CShaderGBuffer();

	// ���f���p�V�F�[�_�̏���������
	void Create(void) override;
	// ���f���p�V�F�[�_�̏I������
	void Delete(void) override;
	// ���f���p�V�F�[�_�̃Z�b�g
	void Begin(const int pass = 0) override;
	// ���f���p�V�F�[�_�̏�������
	void End(void) override;

	// ���_�V�F�[�_�̏�����
	void SetVertexInfo(const D3DXMATRIX mtxW, const float contourScl = 0.2f);
	// �s�N�Z���V�F�[�_�[�̏�����
	void SetPixelInfo(const D3DCOLORVALUE diffColor,const LPDIRECT3DTEXTURE9 texture);

private:
	// �V�F�[�_�v���O�����̃O���[�o���ϐ��ւ̃n���h��
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hMtxWIT;
	D3DXHANDLE	m_hMtxWI;
	D3DXHANDLE	m_hMtxW;

	D3DXHANDLE	m_hMtxLightWVP;
	D3DXHANDLE	m_hMtxLightWV;
	D3DXHANDLE	m_hLightFar;
	D3DXHANDLE	m_hDepthTex;
	D3DXHANDLE	m_hDepthEpsilon;

	D3DXHANDLE	m_hLightDirW;
	D3DXHANDLE	m_hPosEyeW;
	D3DXHANDLE	m_hDiffColor;

	D3DXHANDLE	m_hContourScl;

	D3DXHANDLE	m_hTexture;
	D3DXHANDLE	m_hAnimeDrawTex;

};

#endif