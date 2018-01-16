#ifndef _SHADER_SHADOW_MAP_H_
#define _SHADER_SHADOW_MAP_H_

//*****************************************************************************
//   �V�F�[�_�}���K���̒�`
//*****************************************************************************
class CShaderShadowMap : public CShaderBase
{
public:

	// �f�t�H���g�R���X�g���N�^
	CShaderShadowMap();
	// �f�X�g���N�^
	~CShaderShadowMap();

	// ���f���p�V�F�[�_�̏���������
	void Create(void) override;
	// ���f���p�V�F�[�_�̏I������
	void Delete(void) override;
	// ���f���p�V�F�[�_�̃Z�b�g
	void Begin(const int pass = 0) override;
	// ���f���p�V�F�[�_�̏�������
	void End(void) override;

	// ���_�V�F�[�_�̏�����
	void SetVertexInfo(const D3DXMATRIX mtxW);

private:
	// �V�F�[�_�v���O�����̃O���[�o���ϐ��ւ̃n���h��
	D3DXHANDLE	m_hMtxLightWVP;
	D3DXHANDLE	m_hMtxLightWV;
	D3DXHANDLE	m_hFar;

};

#endif