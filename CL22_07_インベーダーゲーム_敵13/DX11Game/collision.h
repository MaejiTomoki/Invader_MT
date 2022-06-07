//=============================================================================
//
// 衝突判定処理 [collision.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

// ===== インクルード部 ====
#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int CollisionCircle(XMFLOAT2 fA, XMFLOAT2 fB, float fAr, float fBr);
int CollisionRect(float fAx, float fAy,
	float fAw, float fAh, float fBx, float fBy,
	float fBw, float fBh);
