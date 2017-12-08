//=============================================================================
// Xモデルリソース
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "modelX.h"

//   静的メンバ変数宣言
CModelX::MODELX		CModelX::m_modelX[TYPE_MAX] = {};

// テクスチャパス
char CModelX::m_TexName[TYPE_MAX][128] =
{
	"data/MODEL/player.x",
	"data/MODEL/enemy000.x",
	"data/MODEL/block00.x"
};

//*************
// メイン処理
//*************
CModelX::CModelX()
{
}

CModelX::~CModelX()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CModelX::Init()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	for (int j = 0; j < TYPE_MAX; j++)
	{
		// マッピング用テクスチャインターフェースのリリース処理
		for (int i = 0; i < MODEL_MATERIAL_MAX; i++)
		{
			m_modelX[j].pTexture[i] = NULL;
		}

		// モデルのエラーチェック
		if (FAILED(D3DXLoadMeshFromX(m_TexName[j],              // ファイル名
			D3DXMESH_MANAGED,        // 
			pDevice,                 // デバイス
			NULL,
			&m_modelX[j].pBuffMat,        // モデルのマテリアル情報
			NULL,
			&m_modelX[j].NumMat,         // マテリアル数
			&m_modelX[j].pMesh)))          // メッシュ情報
		{
			MessageBox(NULL, "モデルがありません！", "エラー", MB_OK | MB_ICONASTERISK);         // 終了するメッセージ
		}
		D3DXMATERIAL* pMat;
		pMat = (D3DXMATERIAL*)m_modelX[j].pBuffMat->GetBufferPointer();

		for (int i = 0; i < (int)m_modelX[j].NumMat; i++)
		{
			// テクスチャの設定
			if (pMat[i].pTextureFilename != NULL)
			{
				// テクスチャの読み込み(ディスクから)
				if (FAILED(D3DXCreateTextureFromFile(pDevice, pMat[i].pTextureFilename, &m_modelX[j].pTexture[i])))
				{
					MessageBox(NULL, "画像がありません！", "エラー", MB_OK | MB_ICONASTERISK);         // 終了するメッセージ
					// ない時に白いテクスチャを代入
					m_modelX[j].pTexture[i] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
				}
			}
			else
			{
				// ない時に白いテクスチャを代入
				m_modelX[j].pTexture[i] = NULL;
			}
		}
	}
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CModelX::Uninit()
{
	for (int j = 0; j < TYPE_MAX; j++)
	{
		// メッシュ情報のリリース処理
		if (m_modelX[j].pMesh != NULL) {
			m_modelX[j].pMesh->Release();
			m_modelX[j].pMesh = NULL;
		}

		// マテリアル情報のリリース処理
		if (m_modelX[j].pBuffMat != NULL) {
			m_modelX[j].pBuffMat->Release();
			m_modelX[j].pBuffMat = NULL;
		}

		// マッピング用テクスチャインターフェースのリリース処理
		for (int i = 0; i < MODEL_MATERIAL_MAX; i++)
		{
			if (m_modelX[j].pTexture[i] != NULL) {
				m_modelX[j].pTexture[i]->Release();
				m_modelX[j].pTexture[i] = NULL;
			}
		}
	}
}

CModelX::MODELX CModelX::GetModelX(TYPE type)
{
	return m_modelX[type];
}
