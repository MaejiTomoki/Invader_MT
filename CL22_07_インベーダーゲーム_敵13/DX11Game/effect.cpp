//=============================================================================
//
// �e��G�t�F�N�g���� [effect.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "effect.h"
#include "polygon.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_TEXTUREDIR	L"data/texture/"	// �e�N�X�`���t�H���_��

#define MAX_EFFECT			100

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	LPCWSTR		pszTexFName;	// �e�N�X�`�� �t�@�C����
	XMFLOAT2	vSize;			// �\���T�C�Y
	SIZE		sFrame;			// ������
} EFFECT_TYPE;

typedef struct {
	int			nStat;	// ��� (0:����,1:�L��)
	XMFLOAT2	vPos;	// ���W
	int			nType;	// �G�t�F�N�g���
	int			nAnim;	// �A�j���[�V�����Đ��ʒu
	int			nCount;	// �A�j���[�V���� �t���[����
} EFFECT;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*
	g_pTexture[MAX_EFFECTTYPE];	// �e�N�X�`��

static EFFECT_TYPE	g_effectType[MAX_EFFECTTYPE] = {
	{L"dead000.png", {64.0f, 64.0f}, {4, 4}},
};									// �G�t�F�N�g���

static EFFECT	g_effect[MAX_EFFECT];	// �G�t�F�N�g���

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT InitEffect()
{
	HRESULT hr = S_OK;
	WCHAR wszPath[_MAX_PATH];
	ID3D11Device* pDevice = GetDevice();
	int nLen;

	// �e�N�X�`���ǂݍ���
	lstrcpyW(wszPath, EFFECT_TEXTUREDIR);
	//wcscpy(wszPath, EFFECT_TEXTUREDIR);
	nLen = lstrlenW(wszPath);
	//nLen = wcslen(wszPath);
	for (int i = 0; i < MAX_EFFECTTYPE; ++i) {
		lstrcpyW(&wszPath[nLen],
			g_effectType[i].pszTexFName);
		//wcscpy(&wszPath[nLen],
			//g_effectType[i].pszTexFName);
		hr = CreateTextureFromFile(pDevice,
			wszPath, &g_pTexture[i]);
		if (FAILED(hr)) {
			return hr;
		}
	}

	// �G�t�F�N�g��񏉊���
	for (int i = 0; i < MAX_EFFECT; ++i) {
		g_effect[i].nStat = 0;
	}

	return hr;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void UninitEffect()
{
	// �e�N�X�`���J��
	for (int i = 0; i < MAX_EFFECTTYPE; ++i) {
		SAFE_RELEASE(g_pTexture[i]);
	}
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void UpdateEffect()
{
	// �G�t�F�N�g�̍X�V
	EFFECT_TYPE* pEffectType;
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (pEffect->nStat == 0) {
			continue;	// �����Ȃ�X�L�b�v
		}
		// �J�E���^�X�V
		--pEffect->nCount;
		if (pEffect->nCount <= 0) {
			// �A�j���[�V�����X�V
			++pEffect->nAnim;
			pEffectType = &g_effectType[pEffect->nType];
			if (pEffect->nAnim >= pEffectType->sFrame.cx
				* pEffectType->sFrame.cy) {	// �I�[
				pEffect->nStat = 0;	// ����
				continue;
			}
			// �J�E���^������
			pEffect->nCount = 4;
		}
	}
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void DrawEffect()
{
	SetBlendState(BS_ADDITIVE);

	// �G�t�F�N�g�`��
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	EFFECT_TYPE* pEffectType;
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (!pEffect->nStat) {
			// �����Ȃ玟��
			continue;
		}
		pEffectType = &g_effectType[pEffect->nType];
		SetPolygonSize(pEffectType->vSize.x,
					   pEffectType->vSize.y);
		SetPolygonTexture(g_pTexture[pEffect->nType]);
		SetPolygonFrameSize(1.0f / pEffectType->sFrame.cx,
			1.0f / pEffectType->sFrame.cy);
		int u = pEffect->nAnim % pEffectType->sFrame.cx;
		int v = pEffect->nAnim / pEffectType->sFrame.cx;
		SetPolygonUV(u / (float)pEffectType->sFrame.cx,
					 v / (float)pEffectType->sFrame.cy);
		SetPolygonPos(pEffect->vPos.x, pEffect->vPos.y);
		DrawPolygon(pDeviceContext);
	}
	// �t���[����߂��Ă���
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);

	SetBlendState(BS_ALPHABLEND);
}

//=============================================================================
// �G�t�F�N�g�̊J�n����
//=============================================================================
int StartEffect(XMFLOAT2* pPos, int nType)
{
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (pEffect->nStat) {
			// �L���Ȃ�X�L�b�v
			continue;
		}
		// �J�n����
		pEffect->nStat = 1;
		pEffect->vPos = *pPos;
		pEffect->nType = nType;
		pEffect->nAnim = 0;
		pEffect->nCount = 4;
		return i;	// �J�n����
	}
	return -1;		// �J�n�s��
}
