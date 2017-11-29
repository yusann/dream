#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

class CShaderModel;

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

private:
	static CShaderModel *m_pModel;
};

#endif