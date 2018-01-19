#ifndef _MANAGER_H_
#define _MANAGER_H_

#ifdef _DEBUG
#include "imGui/imgui.h"
#include "imGui/imgui_impl_dx9.h"
#endif

//   �O���錾
class CRenderer;
class CSound;
class CTexture;
class CMode;
class CCamera;
class CLight;
class CGBuffer;

#ifdef _DEBUG
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

//*****************************************************************************
//   �}�l�[�W���[�N���X��`
//*****************************************************************************
class CManager
{
public:
	CManager();                                   // �f�t�H���g�R���X�g���N�^
	~CManager();                                  // �f�X�g���N�^
	
	HRESULT Init( HINSTANCE hInstance,             // ����������
			   HWND      hWnd,
			   BOOL      bWindow);              // �t���X�N���[����ONOFF
	void Uninit(void);                             // �I������
	void Update(void);                             // �X�V����
	void Draw(void);                               // �`�揈��

#ifdef _DEBUG
	static void WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return;
	}
#endif
	static void SetMode(CMode *pMode);

	// �擾����
	static CRenderer *GetRenderer() { return m_pRenderer; }
	static CSound    *GetSound()    { return m_pSound; }
	static CCamera   *GetCamera()   { return m_pCamera; }
	static CLight    *GetLight()    { return m_pLight; }
	static CGBuffer  *GetGBuffer()  { return m_pGBuffer; }

private:
	static CRenderer *m_pRenderer;            // �����_���[
	static CSound *m_pSound;
	static CMode *m_pMode;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CGBuffer *m_pGBuffer;
};

#endif