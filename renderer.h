#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "vertexDecl.h"

// ���C�u�����t�@�C�� [�\���v���p�e�B]->[�����J�[]->[����]->[�ǉ��̈ˑ��t�@�C��]�ɋL�q���Ă��\
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")         // �V�X�e�������擾�ɕK�v
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"dinput8.lib")

// �}�N����`
#define NUM_POLYGON       (2)                                  // �|���S����
#define NUM_VERTEX        (4)                                  // ���_��

//*****************************************************************************
//   �����_���N���X�̒�`
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();                                   // �f�t�H���g�R���X�g���N�^
	~CRenderer();                                  // �f�X�g���N�^
	
	HRESULT Init(HWND hWnd, BOOL bWindow);            // ����������
	void Uninit(void);                             // �I������
	bool DrawBegin(void);
	void DrawEnd(void);

	LPDIRECT3DDEVICE9 GetDevice(void);             // �f�o�C�X�̎擾����

private:
	LPDIRECT3D9				m_pD3D;                // Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;          // Device�I�u�W�F�N�g(�`��ɕK�v)
	bool					m_bDraw;
};

#endif