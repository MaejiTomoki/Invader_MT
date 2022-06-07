//=============================================================================
//
// �t���A �G�t�F�N�g���� [flare.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "flare.h"
#include "polygon.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FLARE_TEXTURENAME	L"data/texture/led_lens_flare.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define FLARE_POS_X			0							// �|���S���̕\���ʒu
#define FLARE_POS_Y			0							// �|���S���̕\���ʒu
#define FLARE_SIZE_X		256							// �|���S���̃T�C�Y
#define FLARE_SIZE_Y		256							// �|���S���̃T�C�Y

#define FLARE_ROTSPD		1.0f						// ��]���x
#define FLARE_ZOOM			6.0f						// �����g�嗦
#define FLARE_ZOOM_STEP		0.05f						// �k���X�e�b�v

#define MAX_FLARE			100		// �G�t�F�N�g�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	int			nStat;	// ���
	XMFLOAT2	vPos;	// �ʒu
	float		fAngle;	// �p�x
	float		fZoom;	// �g�嗦
} FLARE;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;			// �e�N�X�`���ւ̃|�C���^
static FLARE						g_flare[MAX_FLARE];	// �G�t�F�N�g���

//=============================================================================
// �t���A �G�t�F�N�g�̏���������
//=============================================================================
HRESULT InitFlare(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// �e�N�X�`���̓ǂݍ���
	hr = CreateTextureFromFile(pDevice, FLARE_TEXTURENAME, &g_pTexture);

	// �ϐ�������
	for (int i = 0; i < MAX_FLARE; ++i) {
		g_flare[i].nStat = 0;
	}

	return hr;
}

//=============================================================================
// �t���A �G�t�F�N�g�̏I������
//=============================================================================
void UninitFlare(void)
{
	// �e�N�X�`�����
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// �t���A �G�t�F�N�g�̍X�V����
//=============================================================================
void UpdateFlare(void)
{
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// �ҋ@���Ȃ�X�L�b�v
		if (pFlare->nStat <= 0) {
			continue;
		}
		// ��]
		pFlare->fAngle += FLARE_ROTSPD;
		// �k��
		pFlare->fZoom -= FLARE_ZOOM_STEP;
		if (pFlare->fZoom <= 0.0f) {
			pFlare->nStat = 0;
		}
	}
}

//=============================================================================
// �t���A �G�t�F�N�g�\������
//=============================================================================
void DrawFlare(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���Z�����ɐݒ�
	SetBlendState(BS_ADDITIVE);

	SetPolygonTexture(g_pTexture);
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// �ҋ@���Ȃ�X�L�b�v
		if (pFlare->nStat <= 0) {
			continue;
		}
		// �\��
		SetPolygonSize(FLARE_SIZE_X * pFlare->fZoom, FLARE_SIZE_Y * pFlare->fZoom);
		SetPolygonPos(pFlare->vPos.x, pFlare->vPos.y);
		for (int i = 0; i < 3; ++i) {
			SetPolygonAngle(pFlare->fAngle + i * 60.0f);
			DrawPolygon(pDeviceContext);
		}
	}

	// ���ɖ߂�
	SetPolygonAngle(0.0f);
	SetBlendState(BS_ALPHABLEND);
}

//=============================================================================
// �t���A �G�t�F�N�g�̊J�n
//=============================================================================
int StartFlare(XMFLOAT2* pPos)
{
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// �g�p���Ȃ�X�L�b�v
		if (pFlare->nStat > 0) {
			continue;
		}
		// �J�n
		pFlare->vPos = *pPos;
		pFlare->fAngle = 30.0f;
		pFlare->fZoom = FLARE_ZOOM;
		pFlare->nStat = 1;
		return i;
	}
	return -1;	// �J�n�ł��Ȃ�������-1��Ԃ�.
}
