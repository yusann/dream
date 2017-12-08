#ifndef _SHADER_BASE_H_
#define _SHADER_BASE_H_

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
// �V�[���N���X
class CShaderBase
{
public:

	CShaderBase();
	~CShaderBase();

	virtual void Create(void) =0;
	virtual void Delete(void) =0;
	virtual void SetTech(void) = 0;
	virtual void Begin(const int pass) = 0;
	virtual void End(void) = 0;

protected:
	void CreateFX(const char* hlslFile);

	// �G�t�F�N�g
	LPD3DXEFFECT            m_pFX;
};

#endif