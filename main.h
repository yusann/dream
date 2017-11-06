#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <stdio.h>
#include <d3dx9.h>
#include <assert.h>
#include <string>
#include <vector>
#include <unordered_map>

#define SCREEN_WIDTH      (1280)									// ウィンドウの幅
#define SCREEN_HEIGHT     (720)										// ウィンドウの高さ
#define SAFE_RELEASE(p)   { if(p){(p)->Release();(p)=NULL;} }		// 終了関数（元のアドレスを代入; NULLで返す）
#define SAFE_UNINIT(p)    { if(p){(p)->Uninit();(p)=NULL;} }		// 終了関数（元のアドレスを代入; NULLで返す）
#define SAFE_DELETE(p)    { if(p){delete (p);(p)=NULL;} }		// 終了関数（元のアドレスを代入; NULLで返す）

#endif