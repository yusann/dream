#ifndef _SCENEMODELX_H_
#define _SCENEMODELX_H_

#include "modelX.h"

//*****************************************************************************
//   X���f���N���X�̒�`
//*****************************************************************************
class CSceneModelX : public CScene
{
public:
	CSceneModelX(int Priority = 3);                                   // �f�t�H���g�R���X�g���N�^
	~CSceneModelX();                                  // �f�X�g���N�^
	
	void Init(void) override;                              // ����������
	void Uninit(void) override;                            // �I������
	void Update(void) override;                            // �X�V����
	void Draw(void) override;                              // �`�揈��
	void DrawDepth(void) override;  // �`�揈��
	void DrawStencilShadow(void) override;  // �`�揈��
	D3DXVECTOR3 GetRot(void) { return m_Rot; }

protected:
	D3DXVECTOR3 m_Rot;      // ��]
	CModelX::MODELX			m_Model;
private:

	LPDIRECT3DVERTEXBUFFER9 m_pCountourVB;
	LPDIRECT3DTEXTURE9 m_pContourTex;
};

#endif