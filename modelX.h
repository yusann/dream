#ifndef _MODELX_H_
#define _MODELX_H_

#define MODEL_MATERIAL_MAX (100)

//*****************************************************************************
//   Xモデルリソースクラスの定義
//*****************************************************************************
class CModelX
{
public:

	// モデル種類
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_BLOCK,
		TYPE_SWITCH,
		TYPE_GOAL,
		TYPE_MAX
	}TYPE;

	// モデル情報
	typedef struct
	{
		LPD3DXMESH			pMesh;              // ライト
		LPD3DXBUFFER		pBuffMat;           // 方向
		DWORD				NumMat;
		LPDIRECT3DTEXTURE9	pTexture[MODEL_MATERIAL_MAX];
	}MODELX;
	CModelX();						// デフォルトコンストラクタ
	~CModelX();						// デストラクタ
	
	static void Init(void);                              // 初期化処理
	static void Uninit(void);                            // 終了処理
	static MODELX GetModelX(TYPE type);					// モデル取得

private:
	static MODELX	m_modelX[TYPE_MAX];					// モデル情報
	static char m_TexName[TYPE_MAX][128];				// モデルパス
};

#endif