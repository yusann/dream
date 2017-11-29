#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShaderModel;

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
class CShaderManager
{
public:
	// ������
	static void Init(void);
	// �I������
	static void Uninit(void);

	static CShaderModel *GetModel() { return m_pModel; }

private:
	static CShaderModel *m_pModel;
};

#endif