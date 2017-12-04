//=============================================================================
// Xモデルバーツ情報リソース
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "motionPartsX.h"

//   静的メンバ変数宣言
std::unordered_map<char*, CMotionPartsX::MOTIONPARTSX>	CMotionPartsX::m_MotionPartsX;

// テクスチャパス
char CMotionPartsX::m_FileName[][128] =
{
	"data/text100.txt",
	"data/text101.txt"
};

//*************
// メイン処理
//*************
//=======================================================================================
//   初期化
//=======================================================================================
void CMotionPartsX::Init()
{
	// ファイル読み込み
	for (int i = 0; i < TYPE_MAX; i++)
	{
		m_MotionPartsX[m_FileName[i]] = LoadFile(m_FileName[i]);
	}
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CMotionPartsX::Uninit()
{
	for (auto CntPartsX = m_MotionPartsX.begin(); CntPartsX != m_MotionPartsX.end(); CntPartsX++)
	{
		// モーション破棄
		for (auto CntMotion = (*CntPartsX).second.Motion.begin(); CntMotion != (*CntPartsX).second.Motion.end(); CntMotion++)
		{
			for (auto CntFrame = (*CntMotion)->KeyFrame.begin(); CntFrame != (*CntMotion)->KeyFrame.end(); CntFrame++)
			{
				(*CntFrame)->Key.clear();
			}
			(*CntMotion)->KeyFrame.clear();
			(*CntMotion)->Collision.clear();
			(*CntMotion)->Sound.clear();
		}
		(*CntPartsX).second.Motion.clear();

		// パーツ破棄
		(*CntPartsX).second.Part.clear();

		// 影破棄
		delete (*CntPartsX).second.pShadow;
		(*CntPartsX).second.pShadow = NULL;
	}
	m_MotionPartsX.clear();
}

//=======================================================================================
//   ファイル読み込み処理
//=======================================================================================
CMotionPartsX::MOTIONPARTSX CMotionPartsX::LoadFile(char *FileName)
{
	MOTIONPARTSX MotionParts;
	char aWork[128];
	int CntParts = -1;
	int CntMotion = -1;
	int CntKeyFrame = -1;
	int CntKey = -1;
	int CntCollision = -1;
	int CntSound = -1;
	FILE* pFile = NULL;
	MotionParts.pShadow = new SHADOW;

	//  ファイルの読み込み
	pFile = fopen(FileName, "r+");
	if (pFile == NULL)
	{
		//  エラーだった場合
		MessageBox(NULL, "ファイルが読み込めませんでした。", "エラーメッセージ", MB_OK | MB_ICONWARNING);
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

			// 影情報
			else if (strcmp(aWork, "SET_SHADOW") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_SHADOW") == 0) {
						break;
					}
					else if (strcmp(aWork, "NUM_X") == 0) {
						fscanf(pFile, "%d", &MotionParts.pShadow->NumX);
					}
					else if (strcmp(aWork, "NUM_Y") == 0) {
						fscanf(pFile, "%d", &MotionParts.pShadow->NumY);
					}
					else if (strcmp(aWork, "RADIUS") == 0) {
						fscanf(pFile, "%f", &MotionParts.pShadow->Radius);
					}
					// スケール
					else if (strcmp(aWork, "SCL") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.pShadow->Scl.x,
							&MotionParts.pShadow->Scl.y,
							&MotionParts.pShadow->Scl.z);
					}
				}
			}

			// オフセット情報
			else if (strcmp(aWork, "SET_OFFSET") == 0) {
				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// オフセット終了
					if (strcmp(aWork, "END_OFFSET") == 0) {
						break;
					}
					else if (strcmp(aWork, "FILENAME") == 0) {
						// 動的確保
						MotionParts.Part.push_back(new PART);
						CntParts++;

						char Path[64];
						fscanf(pFile, "%s", &Path[0]);
						MotionParts.Part[CntParts]->FilePath = Path;
					}
					else if (strcmp(aWork, "PARENT") == 0) {
						fscanf(pFile, "%d", &MotionParts.Part[CntParts]->Parent);
					}
					// 座標
					else if (strcmp(aWork, "POS") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetPos.x,
							&MotionParts.Part[CntParts]->OffSetPos.y,
							&MotionParts.Part[CntParts]->OffSetPos.z);
					}
					// 回転
					else if (strcmp(aWork, "ROT") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetRot.x,
							&MotionParts.Part[CntParts]->OffSetRot.y,
							&MotionParts.Part[CntParts]->OffSetRot.z);
					}
					// スケール
					else if (strcmp(aWork, "SCL") == 0) {
						fscanf(pFile, "%f %f %f",
							&MotionParts.Part[CntParts]->OffSetScl.x,
							&MotionParts.Part[CntParts]->OffSetScl.y,
							&MotionParts.Part[CntParts]->OffSetScl.z);

						//  xファイルの読み込み
						LoadModel(MotionParts.Part[CntParts]);
					}
				}
			}
			// モーション情報
			else if (strcmp(aWork, "SET_MOTION") == 0) {

				while (1)
				{
					fscanf(pFile, "%s", &aWork);
					// ループフラグ
					if (strcmp(aWork, "SET_KEY_FRAME") == 0) {

						MotionParts.Motion.push_back(new MOTION);
						CntMotion++;
						CntKeyFrame = -1;
					}
					// サウンド
					else if (strcmp(aWork, "SET_SOUND") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aWork);
							if (strcmp(aWork, "ID") == 0) {
								MotionParts.Motion[CntMotion]->Sound.push_back(new SOUND);
								CntSound++;
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Sound[CntSound]->ID);
							}
							else if (strcmp(aWork, "FRAME") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Sound[CntSound]->Frame);
							}
							else if (strcmp(aWork, "END_SOUND") == 0) {
								CntSound = -1;
								break;
							}
						}
					}
					// 当たり判定
					else if (strcmp(aWork, "SET_COLLISION") == 0)
					{
						while (1)
						{
							fscanf(pFile, "%s", &aWork);
							// 1つのモーション読み込み終了
							if (strcmp(aWork, "PARTS") == 0) {
								
								MotionParts.Motion[CntMotion]->Collision.push_back(new COLLISION);
								CntCollision++;
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->PartID);
							}
							else if (strcmp(aWork, "POS") == 0) {
								fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.x,
									&MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.y,
									&MotionParts.Motion[CntMotion]->Collision[CntCollision]->Pos.z);
							}
							else if (strcmp(aWork, "SCL") == 0) {
								fscanf(pFile, "%f", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->Scl);
							}
							else if (strcmp(aWork, "START") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->StartFrame);
							}
							else if (strcmp(aWork, "END") == 0) {
								fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->Collision[CntCollision]->EndFrame);
							}
							else if (strcmp(aWork, "END_COLLISION") == 0) {
								CntCollision = -1;
								break;
							}
						}
					}
					// フレーム数
					else if (strcmp(aWork, "FRAME") == 0)
					{
						// キーフレームカウント
						CntKeyFrame++;
						// キーカウンタの初期化
						CntKey = -1;

						// 確保
						MotionParts.Motion[CntMotion]->KeyFrame.push_back(new KEY_FRAME);
						fscanf(pFile, "%d", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Frame);
					}
					// 座標
					else if (strcmp(aWork, "POS") == 0)
					{
						// 確保
						MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key.push_back(new KEY);
						// キーカウント
						CntKey++;

						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Pos.z);
					}
					// 回転
					else if (strcmp(aWork, "ROT") == 0)
					{
						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Rot.z);
					}
					// スケール
					else if (strcmp(aWork, "SCL") == 0)
					{
						fscanf(pFile, "%f %f %f\n", &MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.x,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.y,
							&MotionParts.Motion[CntMotion]->KeyFrame[CntKeyFrame]->Key[CntKey]->Scl.z);
					}
					// 1つのモーション読み込み終了
					else if (strcmp(aWork, "END_MOTION") == 0) {
						break;
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
	return MotionParts;
}

//=======================================================================================
//   モデル読み込み処理
//=======================================================================================
void CMotionPartsX::LoadModel(PART *pPart)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;                // エラーチェックのためNULLを入れる
	pDevice = CManager::GetRenderer()->GetDevice();                           // デバイスのポインタ
	if (pDevice == NULL)                            // エラーチェック
	{
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}
	//  xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(pPart->FilePath.c_str(),				//  ファイル名
		D3DXMESH_MANAGED,															//  オプション
		pDevice,																	//  デバイス
		NULL,
		&pPart->pBuffMat,		//  マテリアル情報
		NULL,
		&pPart->NumMat,			//  マテリアル数
		&pPart->pMesh)))			//  メッシュ情報
	{
		MessageBox(NULL, "xファイルを上手く取得出来ませんでした。", "エラーメッセージ", MB_OK);
		return;
	}

	//  テクスチャ情報取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)pPart->pBuffMat->GetBufferPointer();
	pPart->pTexture = new LPDIRECT3DTEXTURE9[(int)pPart->NumMat];

	//  マテリアルの数分のループ
	for (int j = 0; j < (int)pPart->NumMat; ++j)
	{
		//  テクスチャポインタがある場合
		if (pMat[j].pTextureFilename != NULL)
		{
			//  テクスチャの読み込み( ハードディスクから )	
			if (FAILED(D3DXCreateTextureFromFile(pDevice,	//  デバイス
				pMat[j].pTextureFilename,					//  テクスチャ名
				&pPart->pTexture[j])))		//  呼び込む場所
			{
				//  エラーだった場合
				MessageBox(NULL, "テクスチャインタフェースのポインタがありません。", "エラーメッセージ", MB_OK | MB_ICONWARNING);
				// ない時に白いテクスチャを代入
				pPart->pTexture[j] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
			}
		}
		else
		{
			// ない時に白いテクスチャを代入
			pPart->pTexture[j] = CTexture::GetTexture((int)CTexture::TEXTYPE_WHITE);
		}
	}
}