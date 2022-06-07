//=============================================================================
//
// �Փ˔��菈�� [collision.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "collision.h"


//=============================================================================
// �~���m�̏Փ˔���
//=============================================================================
int CollisionCircle(XMFLOAT2 fA, XMFLOAT2 fB, float fAr, float fBr)
{
	float fDx = fA.x - fB.x;
	float fDy = fA.y - fB.y;
	float fSr = fAr + fBr;
	return fDx * fDx + fDy * fDy <= fSr * fSr;
}

//=============================================================================
// ��`���m�̏Փ˔���
//=============================================================================
int CollisionRect(float fAx, float fAy,
	float fAw, float fAh, float fBx, float fBy,
	float fBw, float fBh)
{
	return fAx - fAw <= fBx + fBw &&
		fBx - fBw <= fAx + fAw &&
		fAy - fAh <= fBy + fBh &&
		fBy - fBh <= fAy + fAh;
}
