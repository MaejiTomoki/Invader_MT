//=============================================================================
//
// �t�F�[�h�C��/�t�F�[�h�A�E�g���� [fade.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

// �t�F�[�h���
enum Efade {
	FADE_NOTE = 0,	// �������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C������
	FADE_OUT,		// �t�F�[�h�A�E�g����

	MAX_FADE
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();


void SetFadeOut(int nNextScene);
int GetFade();
void SetFadeColor(float fR, float fG, float fB);