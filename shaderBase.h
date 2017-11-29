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
	LPDIRECT3DPIXELSHADER9	m_Pixel;		// �s�N�Z���V�F�[�_�[
	LPD3DXCONSTANTTABLE		m_PixelTable;	// �s�N�Z���V�F�[�_�[�̃e�[�u��
	LPDIRECT3DVERTEXSHADER9	m_Vertex;		// ���_�V�F�[�_�[
	LPD3DXCONSTANTTABLE		m_VertexTable;	// ���_�V�F�[�_�[�̃e�[�u��

private:

};

#endif