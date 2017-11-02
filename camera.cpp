//=============================================================================
// カメラ
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "inputKey.h"
#include "xbox360.h"
#include "scene.h"
#include "sceneModelX.h"
#include "sceneMotionPartsX.h"
#include "player.h"

#define CAMERA_MOVE     (0.2f)                    // 移動量
#define CAMERA_ANGLE    (0.05f)                   // 回転量
#define CAMERA_LEN      (50.0f)                   // 距離
#define CAMERA_ZOOM     (0.01f)                   // ズーム速度

//*****************************************************************************
//   静的メンバ変数
//*****************************************************************************
CCamera::CAMERA CCamera::m_pCamera;

//*************
// メイン処理
//*************
CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CCamera::Init()
{
	// カメラの初期化
	m_pCamera.vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);                 // 上方向（Y軸の上）
	m_posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                 // 移動量
	m_Rot = D3DXVECTOR3(0.3f, 0.0f, 0.0f);                         // 角度
	m_length = CAMERA_LEN;
	m_fZoom = D3DX_PI / 3.0f;                                  // 視野角（60°）
	m_Mode = true;
	m_pCamera.posEye.x = (float)cos(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.x;
	m_pCamera.posEye.z = (float)sin(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.z;
	m_pCamera.posEye.y = (float)sin(m_Rot.x) * m_length + m_posMove.y + 15.0f;
	m_pCamera.posAt = m_posMove;
	D3DXMatrixIdentity(&m_pCamera.mtxView);                            // ワールドの中身を初期化
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CCamera::Uninit()
{
	// カメラの初期化
	m_pCamera.vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);                 // 上方向（Y軸の上）
	m_posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);                 // 移動量
	m_Rot = D3DXVECTOR3(1.0f, 0.0f, 0.0f);                 // 角度
	m_length = CAMERA_LEN;
	m_fZoom = D3DX_PI / 3.0f;                                  // 視野角（60°）
	m_pCamera.posEye.x = (float)cos(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.x;
	m_pCamera.posEye.z = (float)sin(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.z;
	m_pCamera.posEye.y = (float)sin(m_Rot.x) * m_length + m_posMove.y;
	m_pCamera.posAt = m_posMove;
	D3DXMatrixIdentity(&m_pCamera.mtxView);                            // ワールドの中身を初期化
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CCamera::Update()
{
	if (CInputKey::GetInputKeyboard()->GetKeyTrigger(DIK_F2))
	{
		m_Mode = !m_Mode;
	}

	if (m_Mode)
	{
		ModeGame();
	}
	else
	{
		ModeDebug();
	}
}
void CCamera::Update(float RotY)
{
	m_Rot.y = RotY;
	m_Rot.x = 0.5f;
	m_pCamera.posEye.x = (float)cos(m_Rot.y + (3.14159265f*0.5f)) * (float)cos(m_Rot.x) * m_length + m_pCamera.posAt.x;
	m_pCamera.posEye.z = (float)sin(m_Rot.y + (3.14159265f*0.5f)) * (float)cos(m_Rot.x) * m_length + m_pCamera.posAt.z;
	m_pCamera.posEye.y = (float)sin(m_Rot.x) * m_length + m_pCamera.posAt.y;
}

//=======================================================================================
//   セット処理
//=======================================================================================
void CCamera::Set(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// プロジェクション行列
	D3DXMATRIX mtxProj;
	D3DXMatrixPerspectiveFovLH(&mtxProj,                               // Fovは画角
		m_fZoom,                          // 画角（視野角）60度にするためπ÷３
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,    // アスペクト比（floatで計算する、float>intなので片方でOK）
		1.0f,                                   // near 必ず0.0fより大きいこと  どこから描画するか
		10000.0f);                                // far どこまで描画するか
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);

	// ビュー行列の作成 LH左手座標系
	D3DXMatrixLookAtLH(&m_pCamera.mtxView, &m_pCamera.posEye, &m_pCamera.posAt, &m_pCamera.vecUp);    // Eye,At,Upの情報からビュー行列(mtxView)を作る関数

	// ビュー行列セット
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);
}

//=======================================================================================
//   ゲーム時カメラ処理
//=======================================================================================
void CCamera::ModeGame(void)
{
	// シーンの取得
	CScene *pScene;
	pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);
	if (pScene == NULL) { return; }

	// プレイヤー情報取得
	CPlayer *pPlayer;
	pPlayer = (CPlayer*)pScene;
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	m_RotYTarget = -pPlayer->GetRot().y;

	// 最短ルートの検知
	if (m_Rot.y - m_RotYTarget >  D3DX_PI) { m_Rot.y -= D3DX_PI * 2; }
	if (m_Rot.y - m_RotYTarget < -D3DX_PI) { m_Rot.y += D3DX_PI * 2; }

	// カメラ注視点設定
	m_pCamera.posAt = playerPos;
	m_pCamera.posAt.y += 15.0f;

	if (CInputKey::GetInputKeyboard()->GetKeyPress(DIK_Q) || CInputKey::GetInputKeyboard()->GetKeyPress(DIK_E)||
		CInputKey::GetInputXbox()->GetXboxPress(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_RIGHT_THUMB))
	{
		m_Rot.y = (m_RotYTarget - m_Rot.y)*0.1f + m_Rot.y;
		m_Rot.x = 0.3f;
	}
	if (CInputKey::GetInputXbox()->GetXboxPress(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_RIGHT_SHOULDER)||
		CInputKey::GetInputXbox()->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::RIGHT).x > 0.5f)
	{
		m_Rot.y -= 0.02f;
	}
	if (CInputKey::GetInputXbox()->GetXboxPress(CInputXbox::CONTROLLER_1, XINPUT_GAMEPAD_LEFT_SHOULDER) ||
		CInputKey::GetInputXbox()->GetAnalogValue(CInputXbox::CONTROLLER_1, CInputXbox::RIGHT).x < -0.5f)
	{
		m_Rot.y += 0.02f;
	}
	m_pCamera.posEye.x = (float)cos(m_Rot.y + (3.14159265f*0.5f)) * (float)cos(m_Rot.x) * CAMERA_LEN + m_pCamera.posAt.x;
	m_pCamera.posEye.z = (float)sin(m_Rot.y + (3.14159265f*0.5f)) * (float)cos(m_Rot.x) * CAMERA_LEN + m_pCamera.posAt.z;
	m_pCamera.posEye.y = (float)sin(m_Rot.x) * CAMERA_LEN + m_pCamera.posAt.y;
}

//=======================================================================================
//   デバッグ時カメラ処理
//=======================================================================================
void CCamera::ModeDebug(void)
{
	  // 移動量のベクトル宣言
	D3DXVECTOR3 work;
	D3DXVECTOR3 move;

	// Y軸無視の長さ（カメラを軸とした長さ）
	work.x = m_pCamera.posAt.x - m_pCamera.posEye.x;    // X軸
	work.y = m_pCamera.posAt.y - m_pCamera.posEye.y;                                      // Y軸
	work.z = m_pCamera.posAt.z - m_pCamera.posEye.z;    // Z軸

	// 移動量ノーマライズ（初期化：方向はそのまま、大きさを１にする）
	D3DXVec3Normalize(&move, &work);

	// キー判定 ///////////////////////////////////////////////////////////////////////////////
	m_length -= CInputKey::GetInputMouse()->GetAxisZ() * 0.1f;
	if (CInputKey::GetInputMouse()->GetCenterPress())
	{
		m_length -= CInputKey::GetInputMouse()->GetAxisZ() * 0.01f;
	}
	if (m_length < 0.0f)
	{
		m_length = 0.0f;
	}
	if (CInputKey::GetInputMouse()->GetLeftPress())
	{
		m_Rot.y -= CInputKey::GetInputMouse()->GetAxisX() * 0.01f;
		m_Rot.x += CInputKey::GetInputMouse()->GetAxisY() * 0.01f;
		if (m_Rot.x > 3.141592f*0.5f)
		{
			m_Rot.x = 3.141592f*0.5f;
		}
		if (m_Rot.x < -3.141592f*0.5f)
		{
			m_Rot.x = -3.141592f*0.5f;
		}
	}
	else if (CInputKey::GetInputMouse()->GetCenterPress())
	{
		float speed = CInputKey::GetInputMouse()->GetAxisX()*1.0f;

		m_posMove.x -= move.z * speed;
		m_posMove.z += move.x * speed;

		speed = CInputKey::GetInputMouse()->GetAxisY()*1.0f;
		m_posMove.y += move.z * speed;
	}
	if (CInputKey::GetInputKeyboard()->GetKeyPress(DIK_X))
	{
		m_length = CAMERA_LEN;
		m_Rot = D3DXVECTOR3(1.0f, 0.0f, 0.0f);                         // 角度
		m_posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_pCamera.posEye.x = (float)cos(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.x;
	m_pCamera.posEye.z = (float)sin(m_Rot.y) * (float)cos(m_Rot.x) * m_length + m_posMove.z;
	m_pCamera.posEye.y = (float)sin(m_Rot.x) * m_length + m_posMove.y;
	m_pCamera.posAt = m_posMove;
}