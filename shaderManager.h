#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShaderModel;
class CShaderManga;

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
class CShaderManager
{
public:
	// 初期化
	static void Init(void);
	// 終了処理
	static void Uninit(void);

	static CShaderModel *GetModel() { return m_pModel; }
	static CShaderManga *GetManga() { return m_pManga; }

private:
	static CShaderModel *m_pModel;
	static CShaderManga *m_pManga;
};

#endif