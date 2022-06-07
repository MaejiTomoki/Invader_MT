//=============================================================================
//
// ���l�\������ [number.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "number.h"
#include "polygon.h"
#include "Texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUMBER_TEXTURENAME	L"data/texture/number000.png"	// �e�N�X�`���t�@�C����

#define NUMBER_FRAME_X		10	// ���t���[����
#define NUMBER_FRAME_Y		1	// �c�t���[����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// �e�N�X�`��

//=============================================================================
// ���l�\���̏���������
//=============================================================================
HRESULT InitNumber()
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		NUMBER_TEXTURENAME, &g_pTexture);

	return hr;
}

//=============================================================================
// ���l�\���̏I������
//=============================================================================
void UninitNumber()
{
	// �e�N�X�`���J��
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// ���l�\������
//=============================================================================
void DrawNumber(XMFLOAT2* pPos, unsigned uNumber,
	int nWidth, float fSizeX, float fSizeY)
{
	ID3D11DeviceContext* pDeviceContext =
		GetDeviceContext();

	// ���l�`��
	SetPolygonSize(fSizeX, fSizeY);
	SetPolygonTexture(g_pTexture);
	SetPolygonFrameSize(1.0f / NUMBER_FRAME_X,
						1.0f / NUMBER_FRAME_Y);
	float fX = pPos->x + fSizeX * (nWidth - 0.5f);
	float fY = pPos->y - fSizeY * 0.5f;
	for (int i = 0; i < nWidth; ++i) {
		unsigned n = uNumber % 10;
		int u = n % NUMBER_FRAME_X;
		int v = n / NUMBER_FRAME_X;
		SetPolygonUV(u / (float)NUMBER_FRAME_X,
					 v / (float)NUMBER_FRAME_Y);
		SetPolygonPos(fX, fY);
		DrawPolygon(pDeviceContext);
		uNumber /= 10;
		fX -= fSizeX;
	}
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}
