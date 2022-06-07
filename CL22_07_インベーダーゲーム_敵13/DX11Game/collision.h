//=============================================================================
//
// �Փ˔��菈�� [collision.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

// ===== �C���N���[�h�� ====
#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int CollisionCircle(XMFLOAT2 fA, XMFLOAT2 fB, float fAr, float fBr);
int CollisionRect(float fAx, float fAy,
	float fAw, float fAh, float fBx, float fBy,
	float fBw, float fBh);
