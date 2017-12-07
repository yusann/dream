//=============================================================================
// 関数集（計算など）
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "equation.h"
#include <random>

//==================================================================================================================================================
//   頂点バッファ設置用
//==================================================================================================================================================
// スケール
void CEquation::SetVertexScaleXY( LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, float fAngle, float fLength, float fRot )
{
	if( pVtxBuffer != NULL){
		// 頂点情報格納用疑似バッファの宣言
		CVertexDecl::VERTEX3D_POS* pVtx = NULL;

		// 頂点バッファをロックして、仮想アドレスを取得する
		pVtxBuffer->Lock( 0, 0, (void**)&pVtx, 0);

		// スケールを設定
		pVtx[0].pos = D3DXVECTOR3( cosf( -fAngle + D3DX_PI + fRot ) * fLength,      // X座標の設定
								   sinf( -fAngle + D3DX_PI + fRot ) * fLength,      // Y座標の設定
								   0.0f );                                   // Z座標の設定
		pVtx[1].pos = D3DXVECTOR3( cosf( fAngle + fRot) * fLength,             // X座標の設定
								   sinf( fAngle + fRot) * fLength,             // Y座標の設定
								   0.0f );                               // Z座標の設定
		pVtx[2].pos = D3DXVECTOR3( cosf( fAngle + D3DX_PI + fRot) * fLength,      // X座標の設定
								   sinf( fAngle + D3DX_PI + fRot) * fLength,      // Y座標の設定
								   0.0f );                                  // Z座標の設定
		pVtx[3].pos = D3DXVECTOR3( cosf( -fAngle + fRot) * fLength,          // X座標の設定
								   sinf( -fAngle + fRot) * fLength,          // Y座標の設定
								   0.0f );                             // Z座標の設定

		// 鍵を開ける
		pVtxBuffer->Unlock();
	}
}

//=======================================================================================================
//   マトリクス計算用
//=======================================================================================================
void CEquation::SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot)
{
	// 変換行列の宣言
	D3DXMATRIX mtxRot;             // ローカル回転
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標

	// ローカル回転の代入
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		Rot.y,
		Rot.x,
		Rot.z);

	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		Pos.x,
		Pos.y,
		Pos.z);

	// ワールド情報処理
	D3DXMatrixIdentity(Out);                  // ワールドの中身を初期化
	D3DXMatrixMultiply(Out, Out, &mtxRot);   // ワールド回転の代入
	D3DXMatrixMultiply(Out, Out, &mtxPos);   // ワールド座標の代入
}
void CEquation::SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
{
	// 変換行列の宣言
	D3DXMATRIX mtxRot;             // ローカル回転
	D3DXMATRIX mtxScl;             // ローカルスケール
	D3DXMATRIX mtxPos;             // ローカル座標

	// ローカル回転の代入
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		Rot.y,
		Rot.x,
		Rot.z);

	// ローカルスケールの代入
	D3DXMatrixScaling(&mtxScl,
		Scl.x,
		Scl.y,
		Scl.z);

	// ローカル座標の代入
	D3DXMatrixTranslation(&mtxPos,
		Pos.x,
		Pos.y,
		Pos.z);

	// ワールド情報処理
	D3DXMatrixIdentity(Out);                  // ワールドの中身を初期化
	D3DXMatrixMultiply(Out, Out, &mtxScl);   // ワールドスケールの代入
	D3DXMatrixMultiply(Out, Out, &mtxRot);   // ワールド回転の代入
	D3DXMatrixMultiply(Out, Out, &mtxPos);   // ワールド座標の代入
}

//==================================================================================================================================================
//   計算用
//==================================================================================================================================================
// 最大値まで
float CEquation::Max( float fMax, float fData , float fPlus)
{
	fData += fPlus;
	if( fData < fMax ) { return fData; }    // 制限値よりデータが小さい場合データをリターン
	return fMax;                            // 制限値をリターン
}

// 最大値来たら最小値に
float CEquation::MaxLoop( float fMin, float fMax, float fData , float fPlus)
{
	fData += fPlus;
	if( fData < fMax ) { return fData; }    // 制限値よりデータが小さい場合データをリターン
	return fMin;                            // 制限値をリターン
}

// 最小値まで
float CEquation::Min( float fMin, float fData , float fMinus)
{
	fData -= fMinus;
	if( fData > fMin ) { return fData; }    // 制限値よりデータが大きい場合データをリターン
	return fMin;                            // 制限値をリターン
}

// 最小値来たら最大値に
float CEquation::MinLoop( float fMax, float fMin, float fData , float fMinus)
{
	fData -= fMinus;
	if( fData > fMin ) { return fData; }    // 制限値よりデータが大きい場合データをリターン
	return fMax;                            // 制限値をリターン
}

// 間のループ
float CEquation::WhileLoop( float fMin, float fMax, float fData , float fPlus, bool* bUse)
{
	if( fData < fMin ) { *bUse = false; }
	if( fData > fMax ) { *bUse = true; }    // 制限値よりデータが大きい場合データをリターン
	if( *bUse == false ) { fData += fPlus; }
	if( *bUse == true  ) { fData -= fPlus; }
	return fData;                            // 制限値をリターン
}

// 乱数
int CEquation::Random( int nMin, int nMax )
{
	std::random_device rd;				//乱数の宣言
	std::uniform_int_distribution<int> data( nMin , nMax );
	int nData = data( rd );
	return nData;                            // 乱数をリターン
}

//==================================================================================================================================================
//   対角線
//==================================================================================================================================================
float CEquation::Length( float fWidth, float fHeight )
{
	float fLength;
	fLength = sqrt( (fWidth * fWidth) + (fHeight * fHeight) ) * 0.5f;
	return fLength;
}

float CEquation::Angle( float fWidth, float fHeight )
{
	float fAngle;
	fAngle = atan2( fHeight , fWidth );
	return fAngle;
}

//--------------------------------------------------------------------------------------
//  視界に入ってるかどうか判定する関数
//--------------------------------------------------------------------------------------
bool IntoView( D3DXVECTOR3 vec1 , D3DXVECTOR3 vec2 )
{
	//  ローカル変数の宣言
	float fVec1Magnitude;								//  第1引数のベクトルの大きさ
	float fVec2Magnitude;								//  第2引数のベクトルの大きさ
	float fInnerProduct;								//  2つのベクトルの内積の結果
	float fAngle;										//  二つのベクトルのなす角( radian)

	//  それぞれのベクトルの大きさを算出する
	fVec1Magnitude = sqrt( vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z );
	fVec2Magnitude = sqrt( vec2.x * vec2.x + vec2.y * vec2.y + vec2.z * vec2.z );

	//  二つのベクトルの内積の結果を算出
	fInnerProduct = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	//  二つのベクトルのなす角( radian )を算出
	fAngle = acosf(( fVec1Magnitude * fVec2Magnitude ) );

	//  視界に入ってるかどうか
	if( fAngle < 0.0f )
	{
		return true;
	}

	return false;
}
