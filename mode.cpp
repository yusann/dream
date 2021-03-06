//=============================================================================
// モード
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "mode.h"
#include "manager.h"
#include "input.h"
#include "inputKey.h"
#include "sound.h"

#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneBillboard.h"
#include "sceneMesh.h"
#include "sceneModelX.h"
#include "fade.h"
#include "object2D.h"
#include "sceneMotionPartsX.h"
#include "player.h"
#include "enemy.h"
#include "block.h"
#include "meshField.h"
#include "skyDome.h"
#include "camera.h"

//*****************************************************************************
//   静的メンバ変数宣言
//*****************************************************************************
CMeshField *CModeGame::m_pMeshField = NULL;
CPlayer *CModeGame::m_pPlayer = NULL;
bool CModeResult::m_Clear = false;

//==================================================================================
//   タイトル
//==================================================================================
//   初期化処理
void CModeTitle::Init(void)
{
	// オブジェクトの配置
	CMeshField::Create();
	CSkyDome::Create(D3DXVECTOR3(0.0f, -2000.0f, 0.0f), 5000.0f, 18, 18);
	char aWork[128];
	D3DXVECTOR3 PosWork;
	D3DXVECTOR3 SclWork;
	FILE* pFile = NULL;

	//  ファイルの読み込み
	pFile = fopen("data/objSave01.txt", "r+");
	if (pFile == NULL)
	{
		//  エラーだった場合
		MessageBox(NULL, "ファイルが読み込めませんでした。", "エラーメッセージ", MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (1)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &aWork);

			// 文字チェック
			//  ロード開始
			if (strcmp(aWork, "LOAD_START") == 0) {
				continue;
			}

			// ブロックセット
			else if (strcmp(aWork, "SET_BLOCK") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_BLOCK") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
					}
					else if (strcmp(aWork, "SCL") == 0) {

						fscanf(pFile, "%f %f %f",
							&SclWork.x,
							&SclWork.y,
							&SclWork.z);
						CBlock::Create(PosWork, SclWork);
					}
				}
			}
			// 終了
			else if (strcmp(aWork, "END_LOAD") == 0) {
				break;
			}
		}
		//  ファイルを閉じる
		fclose(pFile);
	}
	CManager::GetSound()->Play(CSound::BGM_TITLE000);

	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetLen(320.0f);
	pCamera->SetPosAt(D3DXVECTOR3(55.0f,55.0f,0.0f));

	CObject2D::Create(CObject2D::TYPE_BG_TITLE);
	CObject2D::Create(CObject2D::TYPE_UI_PUSH);
}

//   終了処理
void CModeTitle::Uninit(void)
{
	CManager::GetSound()->Stop();
	// オブジェクトの破棄
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//   更新処理
void CModeTitle::Update(void)
{
	static float cameraRot = 0.0f;
	cameraRot += 0.002f;
	if (cameraRot >= 3.1415926f)
	{
		cameraRot = -3.1415926f;
	}
	CCamera *pCamera = CManager::GetCamera();
	pCamera->Update(cameraRot);
	if (CFade::GetFade() != CFade::FADE_NONE) return;
	if (CInputKey::InputGameStart())
	{
		CFade::SetFade(new CModeGame);
	}
}

//   描画処理
void CModeTitle::Draw(void)
{

}

//==================================================================================
//   ゲーム
//==================================================================================
//   初期化処理
void CModeGame::Init(void)
{
	// オブジェクトの配置
	m_pMeshField = CMeshField::Create();
	CSkyDome::Create(D3DXVECTOR3(0.0f, -2000.0f, 0.0f),5000.0f,18,18);

	LoadFile("data/objSave01.txt");

	CObject2D::Create(CObject2D::TYPE_UI_LIFE);
	CManager::GetSound()->Play(CSound::BGM_STAGE000);
	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetRot(D3DXVECTOR3(0.4f,3.0f,0.0f));
}

//   終了処理
void CModeGame::Uninit(void)
{
	CManager::GetSound()->Stop();

	// 変数の破棄
	m_pMeshField = NULL;
	m_pPlayer = NULL;

	// オブジェクトの破棄
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//   更新処理
void CModeGame::Update(void)
{
#ifdef _DEBUG
	static bool player_window = false;
	static bool enemy_window = false;
	static bool block_window = false;
	if (ImGui::Button("Player Window")) player_window ^= 1;
	if (ImGui::Button("Enemy  Window")) enemy_window ^= 1;
	if (ImGui::Button("Block  Window")) block_window ^= 1;
#endif

	// クリア判定
	// シーンの取得用変数
	CScene *pScene;

	if (CInputKey::GetInputKeyboard()->GetKeyTrigger(DIK_F6))
	{
		CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	}

	// 敵全滅チェック
	pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);
	if (pScene == NULL)
	{
		CModeResult::SetClear(true);
		CFade::SetFade(new CModeResult);
	}
#ifdef _DEBUG
	else
	{
		if (enemy_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Enemy Window", &player_window);
			int Cnt = -1;
			// NULLチェック
			while (pScene != NULL)
			{
				// 敵の宣言
				CEnemy *pEnemy;
				pEnemy = (CEnemy*)pScene;

				Cnt++;
				std::string EnemyID = "ID " + std::to_string(Cnt);
				if (ImGui::TreeNode(EnemyID.c_str()))
				{
					pEnemy->ImGui();
					ImGui::TreePop();
				}
				pScene = pScene->SetNextScene();
			}
			ImGui::End();
		}
	}
#endif

	// プレイヤー死亡チェック
	pScene = CScene::GetScene(CScene::OBJTYPE_PLAYER);
	if (pScene == NULL)
	{
		CModeResult::SetClear(false);
		CFade::SetFade(new CModeResult);
	}
#ifdef _DEBUG
	else
	{
		if (player_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Player Window", &player_window);
			CPlayer *pPlayer;
			pPlayer = (CPlayer*)pScene;
			pPlayer->ImGui();
			ImGui::End();
		}
	}
#endif

#ifdef _DEBUG
	// ブロックデバッグ
	if (block_window)
	{
		pScene = CScene::GetScene(CScene::OBJTYPE_BLOCK);
		while (pScene != NULL)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::Begin("Block Window", &player_window);
			CBlock *pBlock;
			pBlock = (CBlock*)pScene;
			int Cnt = -1;
			Cnt++;
			std::string EnemyID = "ID " + std::to_string(Cnt);
			if (ImGui::TreeNode(EnemyID.c_str()))
			{
				pBlock->ImGui();
				ImGui::TreePop();
			}
			pScene = pScene->SetNextScene();
		}
		ImGui::End();
	}
#endif
}

//   描画処理
void CModeGame::Draw(void)
{

}

void CModeGame::LoadFile(char* FileName)
{
	char aWork[128];
	D3DXVECTOR3 PosWork;
	D3DXVECTOR3 SclWork;
	FILE* pFile = NULL;

	//  ファイルの読み込み
	pFile = fopen(FileName, "r+");
	if (pFile == NULL)
	{
		//  エラーだった場合
		MessageBox(NULL, "ファイルが読み込めませんでした。", "エラーメッセージ", MB_OK | MB_ICONWARNING);
		return;
	}
	else
	{
		while (1)
		{
			// 文字読み込み
			fscanf(pFile, "%s", &aWork);

			// 文字チェック
			//  ロード開始
			if (strcmp(aWork, "LOAD_START") == 0) {
				continue;
			}

			// プレイヤーセット
			else if (strcmp(aWork, "SET_PLAYER") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_PLAYER") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
						m_pPlayer = CPlayer::Create(PosWork);
					}
				}
			}

			// 敵セット
			else if (strcmp(aWork, "SET_ENEMY") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_ENEMY") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
						CEnemy::Create(PosWork);
					}
				}
			}

			// ブロックセット
			else if (strcmp(aWork, "SET_BLOCK") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_BLOCK") == 0) {
						break;
					}
					else if (strcmp(aWork, "POS") == 0) {

						fscanf(pFile, "%f %f %f",
							&PosWork.x,
							&PosWork.y,
							&PosWork.z);
					}
					else if (strcmp(aWork, "SCL") == 0) {

						fscanf(pFile, "%f %f %f",
							&SclWork.x,
							&SclWork.y,
							&SclWork.z);
						CBlock::Create(PosWork, SclWork);
					}
				}
			}
			// 終了
			else if (strcmp(aWork, "END_LOAD") == 0) {
				break;
			}
		}
		//  ファイルを閉じる
		fclose(pFile);
	}
}

//==================================================================================
//   リザルト
//==================================================================================
//   初期化処理
void CModeResult::Init(void)
{
	if (m_Clear)
	{
		CObject2D::Create(CObject2D::TYPE_BG_RESULTWIN);
		CManager::GetSound()->Play(CSound::BGM_WIN000);
	}
	else
	{
		CObject2D::Create(CObject2D::TYPE_BG_RESULTLOSE);
		CManager::GetSound()->Play(CSound::BGM_LOSE000);
	}
}

//   終了処理
void CModeResult::Uninit(void)
{
	CManager::GetSound()->Stop();

	// オブジェクトの破棄
	CScene::ReleaseAll(CScene::OBJTYPE_FADE);
}

//   更新処理
void CModeResult::Update(void)
{
	if (CInputKey::InputGameStart())
	{
		CFade::SetFade(new CModeTitle);
	}
}

//   描画処理
void CModeResult::Draw(void)
{

}

//   クリア判定
void CModeResult::SetClear(bool Clear)
{
	m_Clear = Clear;
}
