#ifndef _SCENEMOTIONPARTSX_H_
#define _SCENEMOTIONPARTSX_H_

#include "motionPartsX.h"

// 前方宣言
class CShadowSphere;
#ifdef _DEBUG
class CMeshSphere;
#endif

//*****************************************************************************
//   パーツモーションクラスの定義
//*****************************************************************************
class CSceneMotionPartsX : public CScene
{
public:
	CSceneMotionPartsX(int Priority = 3);                                   // デフォルトコンストラクタ
	~CSceneMotionPartsX();                                  // デストラクタ

	// 球の当たり判定情報
	struct COLLISION_SPHERE
	{
#ifdef _DEBUG
		CMeshSphere			*Sphere;
#endif
		D3DXVECTOR3			Pos;
		float				Scl;
	};

	// モデル
	struct MODEL
	{
		MODEL				*pParent;
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
		D3DXMATRIX			Matrix;
		std::vector<COLLISION_SPHERE*>	Collision;
	};

	void Init(void);                              // 初期化処理
	void Uninit(void);                            // 終了処理
	void Update(void);                            // 更新処理
	void Draw(void);                              // 描画処理
	D3DXVECTOR3 GetRot(void) { return m_Rot; }
	void SetMotion(int MotionID);

protected:
	const int GetKey() { return m_Key; }
	const int GetFrame() { return m_Frame; }
	const int GetMotionFrame() { return m_MotionFrame; }
	const std::vector<COLLISION_SPHERE*> GetCollisionSphere() { return m_CollisionSphere; }

	CMotionPartsX::MOTIONPARTSX *m_pMotionPartsX;
	D3DXVECTOR3				m_Rot;      // 回転
	float					m_Speed;
	float					m_Jump;
	bool m_LastKye;

private:
	struct VECTR3
	{
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
	};

	void UpdateMotion(void);				// マトリクスセット処理
	void UpdateBlendMotion(void);			// 異なるモーションのマトリクスセット処理
	void UpdateLastKeyFrame(void);			// 最後のキーフレーム更新処理

	std::vector<MODEL*>				m_Model;
	D3DXMATRIX						m_Matrix;
	std::vector<COLLISION_SPHERE*>	m_CollisionSphere;
	CShadowSphere*					m_pShadow;
	int m_MotionID;
	int m_Key;
	int m_Frame;
	int m_MotionFrame;

	// 異なるモーションの補間処理用
	std::vector<VECTR3*>	m_BlendData;
	bool					m_Blend;
};

#endif