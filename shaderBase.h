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
	virtual void Set(void) = 0;
	virtual void Clear(void) = 0;

protected:
	void CreateVertex(const char* hlslFile);
	void CreatePixel(const char* hlslFile);

	LPDIRECT3DVERTEXSHADER9	m_pVertex;		// ���_�V�F�[�_�[
	LPD3DXCONSTANTTABLE		m_pVertexTable;	// ���_�V�F�[�_�[�̃e�[�u��
	LPDIRECT3DPIXELSHADER9	m_pPixel;		// �s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE		m_pPixelTable;	// �s�N�Z���V�F�[�_�[�̃e�[�u��

};

#endif