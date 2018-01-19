#ifndef _GBUFFER_H_
#define _GBUFFER_H_

class CDebugShadowMap;

//*****************************************************************************
//   クラスの定義
//*****************************************************************************
// シーンクラス
class CGBuffer
{
public:
	CGBuffer();
	~CGBuffer(){}

	// 初期化
	void Init(LPDIRECT3DDEVICE9 pDevice);
	// 終了処理
	void Uninit(void);

	void SetTexture(LPDIRECT3DDEVICE9 pDevice);
	void SetSurface(LPDIRECT3DDEVICE9 pDevice);
	void SetBack(LPDIRECT3DDEVICE9 pDevice);

	LPDIRECT3DTEXTURE9 GetTextureColor(void)	{ return m_pTextureColor; }
	LPDIRECT3DTEXTURE9 GetTextureNormal(void)	{ return m_pTextureNormal; }
	LPDIRECT3DTEXTURE9 GetTexturePosition(void)	{ return m_pTexturePosition; }

private:
	LPDIRECT3DTEXTURE9 m_pTextureColor;
	LPDIRECT3DTEXTURE9 m_pTextureNormal;
	LPDIRECT3DTEXTURE9 m_pTexturePosition;

	LPDIRECT3DSURFACE9 m_pSurfaceColor;
	LPDIRECT3DSURFACE9 m_pSurfaceNormal;
	LPDIRECT3DSURFACE9 m_pSurfacePosition;

	LPDIRECT3DSURFACE9 m_pSurfaceDepth;

	LPDIRECT3DSURFACE9 m_pBackSurface;
	LPDIRECT3DSURFACE9 m_pBackDepth;

	CDebugShadowMap *m_pDebugDrawColor;
	CDebugShadowMap *m_pDebugDrawNormal;
	CDebugShadowMap *m_pDebugDrawPosition;
};

#endif