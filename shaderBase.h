#ifndef _SHADER_BASE_H_
#define _SHADER_BASE_H_

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
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

	// エフェクト
	LPD3DXEFFECT            m_pFX;
};

#endif