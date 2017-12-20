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
	// ���f���p�V�F�[�_�̃Z�b�g
	void Begin(const int pass = 0) override;
	// ���f���p�V�F�[�_�̏�������
	void End(void) override;

	// ���_�V�F�[�_�̏�����
	void SetVertexInfo(const D3DXMATRIX mtxW);
	// �s�N�Z���V�F�[�_�[�̏�����
	void SetPixelInfo(const LPDIRECT3DTEXTURE9 texture);

private:
	// �V�F�[�_�v���O�����̃O���[�o���ϐ��ւ̃n���h��
	D3DXHANDLE	m_hMtxWVP;
	D3DXHANDLE	m_hTexture;

};

#endif