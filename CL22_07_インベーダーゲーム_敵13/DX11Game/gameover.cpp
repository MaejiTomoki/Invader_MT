//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "title.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/GameOver_02.png"	// �e�N�X�`���t�@�C����

#define GAMEOVER_POS_X		0								// �|���S���̕\���ʒu
#define GAMEOVER_POS_Y		0								// �|���S���̕\���ʒu
#define GAMEOVER_SIZE_X		SCREEN_WIDTH					// �|���S���̃T�C�Y
#define GAMEOVER_SIZE_Y		SCREEN_HEIGHT					// �|���S���̃T�C�Y
#define GAMEOVER_TIMER		(60+30)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��
static int g_nTimer;
//=============================================================================
// �w�i�\���̏���������
//=============================================================================
HRESULT Initgameover()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMEOVER_TIMER;

	return hr;
}

//=============================================================================
// �w�i�\���̏I������
//=============================================================================
void Uninitgameover()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �w�i�\���̍X�V����
//=============================================================================
void Updategameover()
{
	// �X�y�[�X�L�[����������Q�[���J�n
	if (GetKeyRelease(VK_SPACE)) {
		if (GetKeyRelease(VK_SPACE)) {
			SetFadeOut(SCENR_RANKING);
		}
	}
	--g_nTimer;
	if (g_nTimer <= 0) {
		SetFadeOut(SCENR_RANKING);
	}
}

//=============================================================================
// �w�i�\������
//=============================================================================
void Drawgameover()
{
	// �w�i�`��
	SetPolygonPos(GAMEOVER_POS_X, GAMEOVER_POS_Y);
	SetPolygonSize(GAMEOVER_SIZE_X, GAMEOVER_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
