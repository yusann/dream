#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "shaderBase.h"
#include "shaderModel.h"
#include "shaderManga.h"
#include "shaderShadowMap.h"

//*****************************************************************************
//   �N���X�̒�`
//*****************************************************************************
class CShaderManager
{
public:
	typedef enum
	{
		TYPE_GAME_IMAGE = 0,
		TYPE_ANIME,
		TYPE_SHADW_MAP,
		TYPE_MAX,
	}TYPE;
	// ������
	static void Init(void);
	// �I������
	static void Uninit(void);

	static CShaderBase *GetShader(int type) { return m_pShader[type]; }

private:
	static CShaderBase *m_pShader[TYPE_MAX];
};

#endif