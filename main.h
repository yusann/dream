#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#define SCREEN_WIDTH      (1280)									// �E�B���h�E�̕�
#define SCREEN_HEIGHT     (720)										// �E�B���h�E�̍���
#define SAFE_RELEASE(p)   { if(p){(p)->Release();(p)=NULL;} }		// �I���֐��i���̃A�h���X����; NULL�ŕԂ��j
#define SAFE_UNINIT(p)    { if(p){(p)->Uninit();(p)=NULL;} }		// �I���֐��i���̃A�h���X����; NULL�ŕԂ��j
#define SAFE_DELETE(p)    { if(p){delete (p);(p)=NULL;} }		// �I���֐��i���̃A�h���X����; NULL�ŕԂ��j

#endif