//=============================================================================
// テクスチャリソース
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//   静的メンバ変数
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[CTexture::TEXTYPE_MAX] = {};
char CTexture::m_TexName[TEXTYPE_MAX][128] =
{
	"data/TEXTURE/bg.jpg",
	"data/TEXTURE/field000.jpg",
	"data/TEXTURE/kobeni0.png",
	"data/TEXTURE/bullet000.jpg",

	"data/TEXTURE/sky000.jpg",
	"data/TEXTURE/title000.jpg",
	"data/TEXTURE/title001.png",
	"data/TEXTURE/tutorial000.jpg",
	"data/TEXTURE/result000.jpg",
	"data/TEXTURE/result001.jpg",
	"data/TEXTURE/push000.png",

	"data/TEXTURE/particle001.png",
	"data/TEXTURE/particle001.png",
	"data/TEXTURE/particle001.png",

	"data/TEXTURE/life000.jpg",
	"data/TEXTURE/magic000.jpg",
	"data/TEXTURE/gageBG000.png",
	"data/TEXTURE/number000.png"
};

//*************
// メイン処理
//*************
CTexture::CTexture()
{
}

CTexture::~CTexture()
{
}

//=======================================================================================
//   初期化処理
//=======================================================================================
void CTexture::Init()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = NULL;
	pDevice = CManager::GetRenderer()->GetDevice();
	if (pDevice == NULL) {
		MessageBox(NULL, "NULLチェックしてください！", "エラー", MB_OK | MB_ICONASTERISK);         // エラーメッセージ
		return;
	}

	// テクスチャのエラーチェック
	for (int i = 0; i < TEXTYPE_MAX; i++) {
		if( FAILED( D3DXCreateTextureFromFile( pDevice, m_TexName[i], &m_pTexture[i]))) {
			MessageBox( NULL , "画像がありません！" , "エラー" , MB_OK | MB_ICONASTERISK );         // 終了するメッセージ
		}
	}
}

//=======================================================================================
//   終了処理
//=======================================================================================
void CTexture::Uninit()
{
	// テクスチャの破棄
	for (int i = 0; i < TEXTYPE_MAX; i++) {
		SAFE_RELEASE(m_pTexture[i]);
	}
}

//=======================================================================================
//   取得処理
//=======================================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(int nNo) {
	return m_pTexture[nNo];
}