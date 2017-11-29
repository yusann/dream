#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
//   カメラクラス定義
//*****************************************************************************
class CCamera
{
public:
	// デフォルトコンストラクタ
	CCamera();
	// デストラクタ
	~CCamera();
	
	// 初期化
	void Init(void);
	// 終了処理
	void Uninit(void);
	// 更新処理
	void Update(void);
	// タイトル更新処理
	void Update(float RotY);
	// カメラセット
	void Set(void);

	// 座標代入
	void SetPosEye(D3DXVECTOR3 pos)	{ m_PosEye = pos; }
	// 注視点代入
	void SetPosAt(D3DXVECTOR3 pos)	{ m_PosAt = pos; }
	// 距離代入
	void SetLen(float Len)			{ m_Length = Len; }
	// 角度代入
	void SetRot(D3DXVECTOR3 Rot)	{ m_Rot = Rot; }

	// 角度取得
	D3DXVECTOR3 GetRot()		{ return m_Rot; }
	// ビュー行列取得
	D3DXMATRIX	GetMtxView()	{ return m_MtxView; }
	// プロジェクション行列取得
	D3DXMATRIX	GetMtxProj()	{ return m_MtxProj; }
	// 座標取得
	D3DXVECTOR3	GetPosEye()		{ return m_PosEye; }

private:
	void ModeGame(void);
	void ModeDebug(void);

	D3DXMATRIX  m_MtxView;		// ビュー行列
	D3DXMATRIX  m_MtxProj;		// プロジェクション行列
	D3DXVECTOR3 m_PosEye;		// 座標
	D3DXVECTOR3 m_PosAt;		// 注視点
	D3DXVECTOR3 m_VecUp;		// 上方向
	D3DXVECTOR3     m_Move;		// 移動量
	D3DXVECTOR3     m_Rot;		// 角度
	float       m_Length;		// 座標と注視点の距離
	float       m_fZoom;		// 視野角
	bool		m_Mode;			// カメラモード
};

#endif