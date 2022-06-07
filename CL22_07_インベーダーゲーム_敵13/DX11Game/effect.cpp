//=============================================================================
//
// 各種エフェクト処理 [effect.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "effect.h"
#include "polygon.h"
#include "Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EFFECT_TEXTUREDIR	L"data/texture/"	// テクスチャフォルダ名

#define MAX_EFFECT			100

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {
	LPCWSTR		pszTexFName;	// テクスチャ ファイル名
	XMFLOAT2	vSize;			// 表示サイズ
	SIZE		sFrame;			// 分割数
} EFFECT_TYPE;

typedef struct {
	int			nStat;	// 状態 (0:無効,1:有効)
	XMFLOAT2	vPos;	// 座標
	int			nType;	// エフェクト種別
	int			nAnim;	// アニメーション再生位置
	int			nCount;	// アニメーション フレーム数
} EFFECT;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*
	g_pTexture[MAX_EFFECTTYPE];	// テクスチャ

static EFFECT_TYPE	g_effectType[MAX_EFFECTTYPE] = {
	{L"dead000.png", {64.0f, 64.0f}, {4, 4}},
};									// エフェクト種別

static EFFECT	g_effect[MAX_EFFECT];	// エフェクト情報

//=============================================================================
// エフェクトの初期化処理
//=============================================================================
HRESULT InitEffect()
{
	HRESULT hr = S_OK;
	WCHAR wszPath[_MAX_PATH];
	ID3D11Device* pDevice = GetDevice();
	int nLen;

	// テクスチャ読み込み
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

	// エフェクト情報初期化
	for (int i = 0; i < MAX_EFFECT; ++i) {
		g_effect[i].nStat = 0;
	}

	return hr;
}

//=============================================================================
// エフェクトの終了処理
//=============================================================================
void UninitEffect()
{
	// テクスチャ開放
	for (int i = 0; i < MAX_EFFECTTYPE; ++i) {
		SAFE_RELEASE(g_pTexture[i]);
	}
}

//=============================================================================
// エフェクトの更新処理
//=============================================================================
void UpdateEffect()
{
	// エフェクトの更新
	EFFECT_TYPE* pEffectType;
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (pEffect->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		// カウンタ更新
		--pEffect->nCount;
		if (pEffect->nCount <= 0) {
			// アニメーション更新
			++pEffect->nAnim;
			pEffectType = &g_effectType[pEffect->nType];
			if (pEffect->nAnim >= pEffectType->sFrame.cx
				* pEffectType->sFrame.cy) {	// 終端
				pEffect->nStat = 0;	// 消滅
				continue;
			}
			// カウンタ初期化
			pEffect->nCount = 4;
		}
	}
}

//=============================================================================
// エフェクトの描画処理
//=============================================================================
void DrawEffect()
{
	SetBlendState(BS_ADDITIVE);

	// エフェクト描画
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	EFFECT_TYPE* pEffectType;
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (!pEffect->nStat) {
			// 無効なら次へ
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
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);

	SetBlendState(BS_ALPHABLEND);
}

//=============================================================================
// エフェクトの開始処理
//=============================================================================
int StartEffect(XMFLOAT2* pPos, int nType)
{
	EFFECT* pEffect = g_effect;
	for (int i = 0; i < MAX_EFFECT; ++i, ++pEffect) {
		if (pEffect->nStat) {
			// 有効ならスキップ
			continue;
		}
		// 開始処理
		pEffect->nStat = 1;
		pEffect->vPos = *pPos;
		pEffect->nType = nType;
		pEffect->nAnim = 0;
		pEffect->nCount = 4;
		return i;	// 開始成功
	}
	return -1;		// 開始不可
}
