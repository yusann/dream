#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
//   カメラクラス定義
//*****************************************************************************
class CCamera
{
public:
	typedef struct
	{
		D3DXMATRIX  mtxView;     // ビュー行列
		D3DXVECTOR3 posEye;      // 座標
		D3DXVECTOR3 posAt;       // 注視点
		D3DXVECTOR3 vecUp;       // 上方向
	}CAMERA;

	CCamera();                                   // デフォルトコンストラクタ
	~CCamera();                                  // デストラクタ
	
	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);		// 更新処理
	void Update(float RotY);		// 更新処理
	void Set(void);			// セット処理

	// カメラの取得
	static CAMERA GetCamera() {
		return m_pCamera;
	}
	D3DXVECTOR3 GetCameraY() {
		return m_Rot;
	}
	void SetPosEye(D3DXVECTOR3 pos) { m_pCamera.posEye = pos; }
	void SetPosAt(D3DXVECTOR3 pos) { m_pCamera.posAt = pos; }
	void SetLen(float Len) { m_length = Len; }
	void SetRot(D3DXVECTOR3 Rot) { m_Rot = Rot; }

private:
	void ModeGame(void);
	void ModeDebug(void);

	static CAMERA m_pCamera;
	D3DXVECTOR3     m_posMove;     // 移動量
	D3DXVECTOR3     m_Rot;         // 角度
	D3DXVECTOR3		m_LookAtTarget;
	D3DXVECTOR3		m_PosTarget;
	float		m_RotYTarget;
	float       m_length;
	float       m_fZoom;       // ズーム
	bool		m_Mode;
};

#endif