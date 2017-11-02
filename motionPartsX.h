#ifndef _MOTIONPARTSX_H_
#define _MOTIONPARTSX_H_

//*****************************************************************************
//   Xモーションパーツリソースクラスの定義
//*****************************************************************************
class CMotionPartsX
{
public:

	// モデル種類
	typedef enum
	{
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_MAX
	}TYPE;

	// パーツ初期情報
	struct PART
	{
		std::string			FilePath;
		DWORD				NumMat;
		LPD3DXMESH			pMesh;
		LPD3DXBUFFER		pBuffMat;
		LPDIRECT3DTEXTURE9  *pTexture;
		D3DXVECTOR3			OffSetPos;
		D3DXVECTOR3			OffSetRot;
		D3DXVECTOR3			OffSetScl;
		int					Parent;
	};
	// 効果音
	struct SOUND
	{
		int					ID;
		int					Frame;
	};

	// 当たり判定
	struct COLLISION
	{
		int					PartID;
		D3DXVECTOR3			Pos;
		float				Scl;
		int					StartFrame;
		int					EndFrame;
	};

	// キー情報
	struct KEY
	{
		D3DXVECTOR3			Pos;
		D3DXVECTOR3			Rot;
		D3DXVECTOR3			Scl;
	};

	// キーフレーム情報
	struct KEY_FRAME
	{
		int Frame;
		std::vector<KEY*> Key;
	};

	// モーション情報
	struct MOTION
	{
		std::vector<KEY_FRAME*>	KeyFrame;
		std::vector<COLLISION*>	Collision;
		std::vector<SOUND*>		Sound;
	};

	struct  MOTIONPARTSX
	{
		std::vector<PART*>		Part;
		std::vector<MOTION*>	Motion;
	};

	static void Init(void);                              // 初期化処理
	static void Uninit(void);                            // 終了処理
	static MOTIONPARTSX *GetMotionPartsX(TYPE type) { return &m_MotionPartsX[m_FileName[type]]; }					// モデル取得

private:
	static MOTIONPARTSX LoadFile(char *FileName);
	static void LoadModel(PART *pPart);

	static std::unordered_map<char*, MOTIONPARTSX>	m_MotionPartsX;
	static char					m_FileName[][128];		// モデルパス
};

#endif