//=============================================================================
//
// フェードイン/フェードアウト処理 [fade.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

// フェード状態
enum Efade {
	FADE_NOTE = 0,	// 何もしていない
	FADE_IN,		// フェードイン処理
	FADE_OUT,		// フェードアウト処理

	MAX_FADE
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();


void SetFadeOut(int nNextScene);
int GetFade();
void SetFadeColor(float fR, float fG, float fB);