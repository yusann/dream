#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShaderModel;
class CShaderManga;

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
	static CShaderManga *GetManga() { return m_pManga; }

private:
	static CShaderModel *m_pModel;
	static CShaderManga *m_pManga;
};

#endif