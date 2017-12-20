//=============================================================================
// パーツモデル処理
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "shadowSphere.h"
#include "meshSphere.h"
#include "sound.h"
#include "equation.h"
#include "shaderManager.h"

//*************
// メイン処理
//*************
CSceneMotionPartsX::CSceneMotionPartsX(int Priority) :CScene(Priority),
m_MotionID(0),
m_Frame(0),
m_Key(0),
m_MotionFrame(0),
m_Blend(false),
m_LastKye(false),
m_pShadow(NULL)
{
	// メンバ変数の初期化
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

CSceneMotionPartsX::~CSceneMotionPartsX()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CSceneMotionPartsX::Init()
{
	// データ代入
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		m_Model.push_back(new MODEL);
		m_BlendData.push_back(new VECTR3);
		// 階層決め
		if (i == 0)
		{
			m_Model[i]->pParent = NULL;
		}
		else
		{
			m_Model[i]->pParent = m_Model[m_pMotionPartsX->Part[i]->Parent];
		}

		// データ代入
		m_Model[i]->Pos = m_pMotionPartsX->Part[i]->OffSetPos + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Pos;
		m_Model[i]->Rot = m_pMotionPartsX->Part[i]->OffSetRot + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Rot;
		m_Model[i]->Scl = m_pMotionPartsX->Part[i]->OffSetScl + m_pMotionPartsX->Motion[0]->KeyFrame[0]->Key[i]->Scl;

		m_BlendData[i]->Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BlendData[i]->Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BlendData[i]->Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 当たり判定セット
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion.size(); i++)
	{
		for (int j = 0; j < (signed)m_pMotionPartsX->Motion[i]->Collision.size(); j++)
		{
			m_Model[i]->Collision.push_back(new COLLISION_SPHERE);
			m_Model[i]->Collision[j]->Pos = m_pMotionPartsX->Motion[i]->Collision[j]->Pos;
			m_Model[i]->Collision[j]->Scl = m_pMotionPartsX->Motion[i]->Collision[j]->Scl;
#ifdef _DEBUG
			m_Model[i]->Collision[j]->Sphere = CMeshSphere::Create(m_Model[i]->Collision[j]->Pos, m_Model[i]->Collision[j]->Scl, 10, 10, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f));
#endif
		}
	}

	// 影セット
	m_pShadow = CShadowSphere::Create(m_pMotionPartsX->pShadow->NumX,
								m_pMotionPartsX->pShadow->NumY,
								m_pMotionPartsX->pShadow->Radius,
								m_pMotionPartsX->pShadow->Scl);
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CSceneMotionPartsX::Uninit()
{
	// 影破棄
	SAFE_UNINIT(m_pShadow);

	// モデル破棄
	m_Model.clear();
	m_BlendData.clear();
	CScene::Release();
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CSceneMotionPartsX::Update()
{
	CEquation::SetMatrix(&m_Matrix, m_Pos, m_Rot, m_Scl);

	// 影更新
	m_pShadow->Update(m_Pos);

	// ループしないモーション処理
	if (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame <= 0)
	{
		UpdateLastKeyFrame();
		return;
	}

	// フレーム更新
	m_Frame++;

	if (!m_Blend) { UpdateMotion(); }
	else { UpdateBlendMotion(); }
}
// マトリクスセット処理
void CSceneMotionPartsX::UpdateMotion()
{
	// 次のキーフレーム
	int NextKey = m_Key + 1;

	// 次のキーフレームのクリア
	if (NextKey >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		NextKey = 0;

	// パーツ数分ループして補間処理
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		float Frame = (float)m_Frame / (float)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame;

		// 補間量で更新
		m_Model[i]->Pos = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Pos * Frame) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Rot * Frame) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[NextKey]->Key[i]->Scl * Frame) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ワールド座標の代入
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ワールド座標の代入
		}
	}

	// フレーム数チェック
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame)
	{
		// フレームをクリア
		m_Frame = 0;

		// 次のキーフレームへ
		m_Key++;

		// ループモーション
		if (m_Key >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		{
			m_Key = 0;
		}
	}

	// モーションフレーム計算
	m_MotionFrame = 0;
	for (int i = 0; i < m_Key; i++)
	{
		m_MotionFrame += m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[i]->Frame;
	}
	m_MotionFrame += m_Frame;

	// 当たり判定保管用の初期化
	if (!m_CollisionSphere.empty()) { m_CollisionSphere.clear(); }

	// 当たり範囲セット
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Collision.size(); i++)
	{
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->StartFrame > m_MotionFrame) { continue; }
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->EndFrame < m_MotionFrame) { continue; }
		D3DXVec3TransformCoord(&m_Model[m_MotionID]->Collision[i]->Pos,
			&m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Pos,
			&m_Model[m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->PartID]->Matrix);
#ifdef _DEBUG
		m_Model[m_MotionID]->Collision[i]->Sphere->Update(m_Model[m_MotionID]->Collision[i]->Pos,
			m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Scl);
#endif
		m_CollisionSphere.push_back(m_Model[m_MotionID]->Collision[i]);
	}

	// 効果音プレイ
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Sound.size(); i++)
	{
		static int ji = 0;
		if (m_MotionFrame == m_pMotionPartsX->Motion[m_MotionID]->Sound[i]->Frame)
		{
			CManager::GetSound()->Play((CSound::SOUND_LABEL)m_pMotionPartsX->Motion[m_MotionID]->Sound[i]->ID);
		}
	}
}
// ブレンドモーションのマトリクスセット処理
void CSceneMotionPartsX::UpdateBlendMotion()
{
	// パーツ数分ループして補間処理
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		float Frame = (float)m_Frame / (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame*0.5f);

		// 補間量で更新
		m_Model[i]->Pos = (m_BlendData[i]->Pos * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos * Frame) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_BlendData[i]->Rot * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot * Frame) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_BlendData[i]->Scl * (1.0f - Frame)) +
			(m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl * Frame) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ワールド座標の代入
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ワールド座標の代入
		}
	}

	// フレーム数チェック
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame*0.5f)
	{
		// フレームをクリア
		m_Frame = 0;

		// 次のキーフレームへ
		m_Key = 0;

		m_Blend = false;
	}
}
// 最後のキーフレームの更新処理
void CSceneMotionPartsX::UpdateLastKeyFrame()
{
	m_LastKye = true;

	// パーツ数分ループして補間処理
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++)
	{
		// 補間量で更新
		m_Model[i]->Pos = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Pos) +
			m_pMotionPartsX->Part[i]->OffSetPos;
		m_Model[i]->Rot = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Rot) +
			m_pMotionPartsX->Part[i]->OffSetRot;
		m_Model[i]->Scl = (m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Key[i]->Scl) +
			m_pMotionPartsX->Part[i]->OffSetScl;

		CEquation::SetMatrix(&m_Model[i]->Matrix, m_Model[i]->Pos, m_Model[i]->Rot, m_Model[i]->Scl);

		if (m_pMotionPartsX->Part[i]->Parent == -1)
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Matrix);   // ワールド座標の代入
		}
		else
		{
			D3DXMatrixMultiply(&m_Model[i]->Matrix, &m_Model[i]->Matrix, &m_Model[i]->pParent->Matrix);   // ワールド座標の代入
		}
	}

	// フレーム数チェック
	if (m_Frame > m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[m_Key]->Frame)
	{
		// フレームをクリア
		m_Frame = 0;

		// 次のキーフレームへ
		m_Key++;

		// ループモーション
		if (m_Key >= (signed)m_pMotionPartsX->Motion[m_MotionID]->KeyFrame.size())
		{
			m_Key = 0;
		}
	}

	// モーションフレーム計算
	m_MotionFrame = 0;
	for (int i = 0; i < m_Key; i++)
	{
		m_MotionFrame += m_pMotionPartsX->Motion[m_MotionID]->KeyFrame[i]->Frame;
	}
	m_MotionFrame += m_Frame;

	// 当たり判定保管用の初期化
	if (!m_CollisionSphere.empty()) { m_CollisionSphere.clear(); }

	// 当たり範囲セット
	for (int i = 0; i < (signed)m_pMotionPartsX->Motion[m_MotionID]->Collision.size(); i++)
	{
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->StartFrame > m_MotionFrame) { continue; }
		if (m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->EndFrame < m_MotionFrame) { continue; }
		D3DXVec3TransformCoord(&m_Model[m_MotionID]->Collision[i]->Pos,
			&m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Pos,
			&m_Model[m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->PartID]->Matrix);
#ifdef _DEBUG
		m_Model[m_MotionID]->Collision[i]->Sphere->Update(m_Model[m_MotionID]->Collision[i]->Pos,
			m_pMotionPartsX->Motion[m_MotionID]->Collision[i]->Scl);
#endif
		m_CollisionSphere.push_back(m_Model[m_MotionID]->Collision[i]);
	}
}

//=======================================================================================
//   描画処理
//=======================================================================================
void CSceneMotionPartsX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = NULL;                // エラーチェックのためNULLを入れる
	pDevice = CManager::GetRenderer()->GetDevice();                           // デバイスのポインタを取得

	if (pDevice == NULL)                            // エラーチェック
	{
		MessageBox(NULL, "InitのpDeveceのNULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	// 影描画
	m_pShadow->Draw();

	// 輪郭
	// シェーダの取得
	CShaderManga *pShaderManga = (CShaderManga*)CShaderManager::GetShader(CShaderManager::TYPE_ANIME);
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {

		// NULLチェック
		if (m_pMotionPartsX->Part[i]->pBuffMat == NULL) { return; }
		D3DXMATERIAL*	pMat = NULL;					//  マテリアル

														// ワールド情報セット
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[i]->Matrix);

		D3DMATERIAL9 matDef;
		pDevice->GetMaterial(&matDef);                 // 現在デバイスに設定されてるアテリアル情報を取得

		pMat = (D3DXMATERIAL*)m_pMotionPartsX->Part[i]->pBuffMat->GetBufferPointer();

		// 頂点シェーダの代入
		pShaderManga->SetVertexInfo(m_Model[i]->Matrix);

		for (int j = 0; j < (int)m_pMotionPartsX->Part[i]->NumMat; j++)
		{
			pShaderManga->Begin(2);
			// メッシュの描画
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			m_pMotionPartsX->Part[i]->pMesh->DrawSubset(j);
			pShaderManga->End();
		}
	}


	// 全パーツ分ループ
	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {

	// NULLチェック
	if (m_pMotionPartsX->Part[i]->pBuffMat == NULL) { return; }
		D3DXMATERIAL*	pMat = NULL;					//  マテリアル

		// ワールド情報セット
		pDevice->SetTransform(D3DTS_WORLD, &m_Model[i]->Matrix);

		D3DMATERIAL9 matDef;
		pDevice->GetMaterial(&matDef);                 // 現在デバイスに設定されてるアテリアル情報を取得

		pMat = (D3DXMATERIAL*)m_pMotionPartsX->Part[i]->pBuffMat->GetBufferPointer();

		// シェーダの取得
		pShaderManga->SetVertexInfo(m_Model[i]->Matrix);

		for (int j = 0; j < (int)m_pMotionPartsX->Part[i]->NumMat; j++)
		{
			if (m_pMotionPartsX->Part[i]->pTexture[j] != NULL)
			{
				// ピクセルシェーダの設定
				pShaderManga->SetPixelInfo(pMat[j].MatD3D.Diffuse, m_pMotionPartsX->Part[i]->pTexture[j]);
				pShaderManga->Begin();
			}
			else
			{
				// ピクセルシェーダの設定
				pShaderManga->SetPixelInfo(pMat[j].MatD3D.Diffuse, NULL);
				pShaderManga->Begin(1);
			}
			// メッシュの描画
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			m_pMotionPartsX->Part[i]->pMesh->DrawSubset(j);
			pShaderManga->End();
		}
	}
}

void CSceneMotionPartsX::SetMotion(int MotionID)
{
	if (m_MotionID == MotionID)
		return;

	for (int i = 0; i < (signed)m_pMotionPartsX->Part.size(); i++) {
		m_BlendData[i]->Pos = m_Model[i]->Pos - m_pMotionPartsX->Part[i]->OffSetPos;
		m_BlendData[i]->Rot = m_Model[i]->Rot - m_pMotionPartsX->Part[i]->OffSetRot;
		m_BlendData[i]->Scl = m_Model[i]->Scl - m_pMotionPartsX->Part[i]->OffSetScl;
	}
	m_Blend = true;
	m_MotionID = MotionID;
	m_Key = 0;
	m_Frame = 0;
	m_LastKye = false;
}