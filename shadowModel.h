#ifndef _SHADOW_MODEL_H_
#define _SHADOW_MODEL_H_

//*****************************************************************************
//   影クラス定義
//*****************************************************************************
class CShadowModel : public CScene2D
{
public:
	CShadowModel();					// デフォルトコンストラクタ
	CShadowModel(const LPD3DXMESH pMesh);
	~CShadowModel();					// デストラクタ

	static CShadowModel *Create(const LPD3DXMESH pMesh);                  // 作成

	void Init(void);        // 初期化処理
	void Uninit(void);      // 終了処理
	void Update(void);
	void Draw(void);        // 描画処理
	void SetMatrix(const D3DXMATRIX matrix) {
		m_Matrix = matrix;
	}

private:
	struct SHADOWVOLUME {						//----- シャドウボリューム
		D3DXVECTOR3		*pVertex;				// 座標
		int				iNumVertex;				// 頂点数
	};

	HRESULT BuildShadowVolume( LPD3DXMESH pMesh, D3DXVECTOR3 vLight);
	void AddEdge(WORD* pEdge, DWORD* pdwNumEdge, WORD v0, WORD v1);

	SHADOWVOLUME	m_Shadow;						// シャドウボリューム
	LPD3DXMESH		m_pMesh;
	D3DXMATRIX		m_Matrix;

	static int m_MaxID;
};

#endif