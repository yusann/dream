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
	
	void Init(void);                              // ����������
	void Uninit(void);                            // �I������
	void Update(void);                            // �X�V����
	void Draw(void);                              // �`�揈��
	D3DXVECTOR3 GetRot(void) { return m_Rot; }

protected:
	D3DXVECTOR3 m_vecUp;    // �����
	D3DXVECTOR3 m_Rot;      // ��]
	CModelX::MODELX			m_Model;
};

#endif