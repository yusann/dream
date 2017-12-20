//*****************************************************************************
//   インクルードファイル
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "sceneModelX.h"
#include "shaderManager.h"

//=======================================================================================
//   コンストラクタ
//=======================================================================================
CSceneModelX::CSceneModelX(int Priority) :CScene(Priority),
m_Rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	// メンバ変数の初期化
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//=======================================================================================
//   デストラクタ
//=======================================================================================
CSceneModelX::~CSceneModelX()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CSceneModelX::Init()
{
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CSceneModelX::Uninit()
{
	CScene::Release();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CSceneModelX::Update()
{
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CSceneModelX::Draw()
{
	if (m_Model.pBuffMat == NULL) { return; }

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	
	// 変換行列の宣言
	D3DXMATRIX mtxRot;             // ローカル回転
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標
	D3DXMATRIX mtxWorld;           // ワールド情報
	
	// ローカル回転の代入
	D3DXMatrixRotationYawPitchRoll( &mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z );

	// ローカルスケールの代入
	D3DXMatrixScaling( &mtxScl,
					   m_Scl.x,
					   m_Scl.y,
					   m_Scl.z );

	// ローカル座標の代入
	D3DXMatrixTranslation( &mtxPos,
						   m_Pos.x,
						   m_Pos.y,
						   m_Pos.z );
	
	// ワールド情報処理
	D3DXMatrixIdentity( &mtxWorld );                       // ワールドの中身を初期化
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxRot );   // ワールド回転の代入
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxScl );   // ワールドスケールの代入
	D3DXMatrixMultiply( &mtxWorld, &mtxWorld, &mtxPos );   // ワールド座標の代入
	pDevice->SetTransform( D3DTS_WORLD, &mtxWorld );       // ワールド情報セット

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial( &matDef );                 // 現在デバイスに設定されてるアテリアル情報を取得

	D3DXMATERIAL* pMat;
	pMat = (D3DXMATERIAL*)m_Model.pBuffMat->GetBufferPointer();


	// 輪郭シェーダのセット
	CShaderManga *pShaderManga = (CShaderManga*)CShaderManager::GetShader(CShaderManager::TYPE_ANIME);
	pShaderManga->SetVertexInfo(mtxWorld, 0.01f);

	for (int i = 0; i < (int)m_Model.NumMat; i++)
	{
		pShaderManga->Begin(2);
		// メッシュの描画
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		m_Model.pMesh->DrawSubset(i);
		// シェーダクリア
		pShaderManga->End();
	}

	// シェーダのセット
	pShaderManga->SetVertexInfo(mtxWorld);

	for( int i = 0; i < (int)m_Model.NumMat; i++ )
	{

		if (pMat[i].pTextureFilename != NULL)
		{
			// マテリアルの設定
			pShaderManga->SetPixelInfo(pMat[i].MatD3D.Diffuse, m_Model.pTexture[i]);
			pShaderManga->Begin();
		}
		else
		{
			// マテリアルの設定
			pShaderManga->SetPixelInfo(pMat[i].MatD3D.Diffuse, NULL);
			pShaderManga->Begin(1);
		}
		// メッシュの描画
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_Model.pMesh->DrawSubset(i);
		// シェーダクリア
		pShaderManga->End();
	}
}