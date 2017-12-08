#ifndef _SHADER_MODEL_H_
#define _SHADER_MODEL_H_

//*****************************************************************************
//   �V�F�[�_���f���̒�`
//*****************************************************************************
class CShaderModel : public CShaderBase
{
public:

	// �f�t�H���g�R���X�g���N�^
	CShaderModel();
	// �f�X�g���N�^
	~CShaderModel();

	// ���f���p�V�F�[�_�̏���������
	void Create(void) override;
	// ���f���p�V�F�[�_�̏I������
	void Delete(void) override;
	// �e�N�j�b�N�̐ݒ�
	void SetTech(void) override;
	// ���f���p�V�F�[�_�̃Z�b�g
	void Begin(const int pass = 0) override;
	// ���f���p�V�F�[�_�̏�������
	void End(void) override;

	// ���_�V�F�[�_�̏�����
	void SetVertexInfo(const D3DXMATRIX mtxW);
	// �s�N�Z���V�F�[�_�[�̏�����
	void SetPixelInfo(const D3DCOLORVALUE diffColor,const LPDIRECT3DTEXTURE9 texture, const float specularPower = 60.0f);

private:
	// �e�N�j�b�N�ւ̃n���h��
	D3DXHANDLE	m_hTech;

	// �V�F�[�_�v���O�����̃O���[�o���ϐ��ւ̃n���h��
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hMtxW;

	D3DXHANDLE	m_hLightDirW;
	D3DXHANDLE	m_hPosEyeW;
	D3DXHANDLE	m_hDiffColor;
	D3DXHANDLE	m_hSpecularPower;

	D3DXHANDLE	m_hTexture;

};

#endif