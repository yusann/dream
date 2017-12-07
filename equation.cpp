//=============================================================================
// �֐��W�i�v�Z�Ȃǁj
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "equation.h"
#include <random>

//==================================================================================================================================================
//   ���_�o�b�t�@�ݒu�p
//==================================================================================================================================================
// �X�P�[��
void CEquation::SetVertexScaleXY( LPDIRECT3DVERTEXBUFFER9 pVtxBuffer, float fAngle, float fLength, float fRot )
{
	if( pVtxBuffer != NULL){
		// ���_���i�[�p�^���o�b�t�@�̐錾
		CVertexDecl::VERTEX3D_POS* pVtx = NULL;

		// ���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
		pVtxBuffer->Lock( 0, 0, (void**)&pVtx, 0);

		// �X�P�[����ݒ�
		pVtx[0].pos = D3DXVECTOR3( cosf( -fAngle + D3DX_PI + fRot ) * fLength,      // X���W�̐ݒ�
								   sinf( -fAngle + D3DX_PI + fRot ) * fLength,      // Y���W�̐ݒ�
								   0.0f );                                   // Z���W�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3( cosf( fAngle + fRot) * fLength,             // X���W�̐ݒ�
								   sinf( fAngle + fRot) * fLength,             // Y���W�̐ݒ�
								   0.0f );                               // Z���W�̐ݒ�
		pVtx[2].pos = D3DXVECTOR3( cosf( fAngle + D3DX_PI + fRot) * fLength,      // X���W�̐ݒ�
								   sinf( fAngle + D3DX_PI + fRot) * fLength,      // Y���W�̐ݒ�
								   0.0f );                                  // Z���W�̐ݒ�
		pVtx[3].pos = D3DXVECTOR3( cosf( -fAngle + fRot) * fLength,          // X���W�̐ݒ�
								   sinf( -fAngle + fRot) * fLength,          // Y���W�̐ݒ�
								   0.0f );                             // Z���W�̐ݒ�

		// �����J����
		pVtxBuffer->Unlock();
	}
}

//=======================================================================================================
//   �}�g���N�X�v�Z�p
//=======================================================================================================
void CEquation::SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot)
{
	// �ϊ��s��̐錾
	D3DXMATRIX mtxRot;             // ���[�J����]
	D3DXMATRIX mtxScl;             // ���[�J���X�P�[��
	D3DXMATRIX mtxPos;             // ���[�J�����W

	// ���[�J����]�̑��
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		Rot.y,
		Rot.x,
		Rot.z);

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		Pos.x,
		Pos.y,
		Pos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(Out);                  // ���[���h�̒��g��������
	D3DXMatrixMultiply(Out, Out, &mtxRot);   // ���[���h��]�̑��
	D3DXMatrixMultiply(Out, Out, &mtxPos);   // ���[���h���W�̑��
}
void CEquation::SetMatrix(D3DXMATRIX *Out, D3DXVECTOR3 Pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scl)
{
	// �ϊ��s��̐錾
	D3DXMATRIX mtxRot;             // ���[�J����]
	D3DXMATRIX mtxScl;             // ���[�J���X�P�[��
	D3DXMATRIX mtxPos;             // ���[�J�����W

	// ���[�J����]�̑��
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		Rot.y,
		Rot.x,
		Rot.z);

	// ���[�J���X�P�[���̑��
	D3DXMatrixScaling(&mtxScl,
		Scl.x,
		Scl.y,
		Scl.z);

	// ���[�J�����W�̑��
	D3DXMatrixTranslation(&mtxPos,
		Pos.x,
		Pos.y,
		Pos.z);

	// ���[���h��񏈗�
	D3DXMatrixIdentity(Out);                  // ���[���h�̒��g��������
	D3DXMatrixMultiply(Out, Out, &mtxScl);   // ���[���h�X�P�[���̑��
	D3DXMatrixMultiply(Out, Out, &mtxRot);   // ���[���h��]�̑��
	D3DXMatrixMultiply(Out, Out, &mtxPos);   // ���[���h���W�̑��
}

//==================================================================================================================================================
//   �v�Z�p
//==================================================================================================================================================
// �ő�l�܂�
float CEquation::Max( float fMax, float fData , float fPlus)
{
	fData += fPlus;
	if( fData < fMax ) { return fData; }    // �����l���f�[�^���������ꍇ�f�[�^�����^�[��
	return fMax;                            // �����l�����^�[��
}

// �ő�l������ŏ��l��
float CEquation::MaxLoop( float fMin, float fMax, float fData , float fPlus)
{
	fData += fPlus;
	if( fData < fMax ) { return fData; }    // �����l���f�[�^���������ꍇ�f�[�^�����^�[��
	return fMin;                            // �����l�����^�[��
}

// �ŏ��l�܂�
float CEquation::Min( float fMin, float fData , float fMinus)
{
	fData -= fMinus;
	if( fData > fMin ) { return fData; }    // �����l���f�[�^���傫���ꍇ�f�[�^�����^�[��
	return fMin;                            // �����l�����^�[��
}

// �ŏ��l������ő�l��
float CEquation::MinLoop( float fMax, float fMin, float fData , float fMinus)
{
	fData -= fMinus;
	if( fData > fMin ) { return fData; }    // �����l���f�[�^���傫���ꍇ�f�[�^�����^�[��
	return fMax;                            // �����l�����^�[��
}

// �Ԃ̃��[�v
float CEquation::WhileLoop( float fMin, float fMax, float fData , float fPlus, bool* bUse)
{
	if( fData < fMin ) { *bUse = false; }
	if( fData > fMax ) { *bUse = true; }    // �����l���f�[�^���傫���ꍇ�f�[�^�����^�[��
	if( *bUse == false ) { fData += fPlus; }
	if( *bUse == true  ) { fData -= fPlus; }
	return fData;                            // �����l�����^�[��
}

// ����
int CEquation::Random( int nMin, int nMax )
{
	std::random_device rd;				//�����̐錾
	std::uniform_int_distribution<int> data( nMin , nMax );
	int nData = data( rd );
	return nData;                            // ���������^�[��
}

//==================================================================================================================================================
//   �Ίp��
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
//  ���E�ɓ����Ă邩�ǂ������肷��֐�
//--------------------------------------------------------------------------------------
bool IntoView( D3DXVECTOR3 vec1 , D3DXVECTOR3 vec2 )
{
	//  ���[�J���ϐ��̐錾
	float fVec1Magnitude;								//  ��1�����̃x�N�g���̑傫��
	float fVec2Magnitude;								//  ��2�����̃x�N�g���̑傫��
	float fInnerProduct;								//  2�̃x�N�g���̓��ς̌���
	float fAngle;										//  ��̃x�N�g���̂Ȃ��p( radian)

	//  ���ꂼ��̃x�N�g���̑傫�����Z�o����
	fVec1Magnitude = sqrt( vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z );
	fVec2Magnitude = sqrt( vec2.x * vec2.x + vec2.y * vec2.y + vec2.z * vec2.z );

	//  ��̃x�N�g���̓��ς̌��ʂ��Z�o
	fInnerProduct = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	//  ��̃x�N�g���̂Ȃ��p( radian )���Z�o
	fAngle = acosf(( fVec1Magnitude * fVec2Magnitude ) );

	//  ���E�ɓ����Ă邩�ǂ���
	if( fAngle < 0.0f )
	{
		return true;
	}

	return false;
}
