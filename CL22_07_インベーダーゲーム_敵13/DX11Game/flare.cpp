//=============================================================================
//
// フレア エフェクト処理 [flare.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "flare.h"
#include "polygon.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FLARE_TEXTURENAME	L"data/texture/led_lens_flare.png"	// 読み込むテクスチャファイル名

#define FLARE_POS_X			0							// ポリゴンの表示位置
#define FLARE_POS_Y			0							// ポリゴンの表示位置
#define FLARE_SIZE_X		256							// ポリゴンのサイズ
#define FLARE_SIZE_Y		256							// ポリゴンのサイズ

#define FLARE_ROTSPD		1.0f						// 回転速度
#define FLARE_ZOOM			6.0f						// 初期拡大率
#define FLARE_ZOOM_STEP		0.05f						// 縮小ステップ

#define MAX_FLARE			100		// エフェクト最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {
	int			nStat;	// 状態
	XMFLOAT2	vPos;	// 位置
	float		fAngle;	// 角度
	float		fZoom;	// 拡大率
} FLARE;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;			// テクスチャへのポインタ
static FLARE						g_flare[MAX_FLARE];	// エフェクト情報

//=============================================================================
// フレア エフェクトの初期化処理
//=============================================================================
HRESULT InitFlare(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr = S_OK;

	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, FLARE_TEXTURENAME, &g_pTexture);

	// 変数初期化
	for (int i = 0; i < MAX_FLARE; ++i) {
		g_flare[i].nStat = 0;
	}

	return hr;
}

//=============================================================================
// フレア エフェクトの終了処理
//=============================================================================
void UninitFlare(void)
{
	// テクスチャ解放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// フレア エフェクトの更新処理
//=============================================================================
void UpdateFlare(void)
{
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// 待機中ならスキップ
		if (pFlare->nStat <= 0) {
			continue;
		}
		// 回転
		pFlare->fAngle += FLARE_ROTSPD;
		// 縮小
		pFlare->fZoom -= FLARE_ZOOM_STEP;
		if (pFlare->fZoom <= 0.0f) {
			pFlare->nStat = 0;
		}
	}
}

//=============================================================================
// フレア エフェクト表示処理
//=============================================================================
void DrawFlare(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 加算合成に設定
	SetBlendState(BS_ADDITIVE);

	SetPolygonTexture(g_pTexture);
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// 待機中ならスキップ
		if (pFlare->nStat <= 0) {
			continue;
		}
		// 表示
		SetPolygonSize(FLARE_SIZE_X * pFlare->fZoom, FLARE_SIZE_Y * pFlare->fZoom);
		SetPolygonPos(pFlare->vPos.x, pFlare->vPos.y);
		for (int i = 0; i < 3; ++i) {
			SetPolygonAngle(pFlare->fAngle + i * 60.0f);
			DrawPolygon(pDeviceContext);
		}
	}

	// 元に戻す
	SetPolygonAngle(0.0f);
	SetBlendState(BS_ALPHABLEND);
}

//=============================================================================
// フレア エフェクトの開始
//=============================================================================
int StartFlare(XMFLOAT2* pPos)
{
	FLARE* pFlare = g_flare;
	for (int i = 0; i < MAX_FLARE; ++i, pFlare++) {
		// 使用中ならスキップ
		if (pFlare->nStat > 0) {
			continue;
		}
		// 開始
		pFlare->vPos = *pPos;
		pFlare->fAngle = 30.0f;
		pFlare->fZoom = FLARE_ZOOM;
		pFlare->nStat = 1;
		return i;
	}
	return -1;	// 開始できなかったら-1を返す.
}
