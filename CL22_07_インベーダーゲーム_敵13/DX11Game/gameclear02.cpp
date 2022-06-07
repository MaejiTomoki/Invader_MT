//=============================================================================
//
// �^�C�g����ʏ��� [GameClear02.cpp]
// Author : �O�n�q�M
//
//=============================================================================
#include "gameclear02.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMECLEAR02_TEXTURENAME	L"data/texture/GameClear_02.png"	// �e�N�X�`���t�@�C����

#define GAMECLEAR02_POS_X		0								// �|���S���̕\���ʒu
#define GAMECLEAR02_POS_Y		0								// �|���S���̕\���ʒu
#define GAMECLEAR02_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMECLEAR02_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y
#define GAMECLEAR02_TIMER		(60+30)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTextureGAMECLEAR02;				// �e�N�X�`��
static int g_nTimerGAMECLEAR02;
//=============================================================================
// �w�i�\���̏���������
//=============================================================================
HRESULT InitGameClear02()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR02_TEXTURENAME, &g_pTextureGAMECLEAR02);

	g_nTimerGAMECLEAR02 = GAMECLEAR02_TIMER;

	return hr;
}

//=============================================================================
// �w�i�\���̏I������
//=============================================================================
void UninitGameClear02()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTextureGAMECLEAR02);
}

//=============================================================================
// �w�i�\���̍X�V����
//=============================================================================
void UpdateGameClear02()
{
	// �X�y�[�X�L�[����������Q�[���J�n
	if (GetKeyRelease(VK_SPACE)) {
		if (GetKeyRelease(VK_SPACE)) {
			SetFadeOut(SCENR_RANKING);
		}
	}
	--g_nTimerGAMECLEAR02;
	if (g_nTimerGAMECLEAR02 <= 0) {
		SetFadeOut(SCENR_RANKING);
	}
}

//=============================================================================
// �w�i�\������
//=============================================================================
void DrawGameClear02()
{
	// �w�i�`��
	SetPolygonPos(GAMECLEAR02_POS_X, GAMECLEAR02_POS_Y);
	SetPolygonSize(GAMECLEAR02_SIZE_X, GAMECLEAR02_SIZE_Y);
	SetPolygonTexture(g_pTextureGAMECLEAR02);
	DrawPolygon(GetDeviceContext());
}
