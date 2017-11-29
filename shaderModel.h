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
	void Set(void) override;
	// ���f���p�V�F�[�_�̏�������
	void Clear(void) override;

	// ���_�V�F�[�_�̏�����
	void SetVertexInfo(const D3DXMATRIX mtxW, const D3DCOLORVALUE diffColor);
	// �s�N�Z���V�F�[�_�[�̏�����
	void SetPixelInfo( const float specularPower, const float specular, const D3DXVECTOR3 modelPos);
	// �e�N�X�`��ID�̎擾
	UINT GetSamplerIndex(void);

private:
	void CreateVertex(void);
	void CreatePixel(void);
};

#endif