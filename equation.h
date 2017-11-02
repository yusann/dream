#ifndef _EQUATION_H_
#define _EQUATION_H_

//*****************************************************************************
//   関数集クラスの定義
//*****************************************************************************
class CEquation
{
public:
	static void SetVertexScaleXY(LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, float fAngle, float fLength, float fRot);
	static void SetVertexScaleXZ(LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, float fAngle, float fLength, float fRot);
	static void SetVertexTex(LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize);
	static void SetVertexColor(LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, D3DXCOLOR color);

	static void SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot);
	static void SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl);

	static float Max(float fMax, float fData, float fPlus);
	static float MaxLoop(float fMin, float fMax, float fData, float fPlus);
	static float Min(float fMin, float fData, float fMinus);
	static float MinLoop(float fMax, float fMin, float fData, float fMinus);
	static float WhileLoop(float fMin, float fMax, float fData, float fPlus, bool* bUse);
	static int   Random(int nMin, int nMax);

	static float Length(float fWidth, float fHeight);
	static float Angle(float fWidth, float fHeight);

private:

};

#endif
