//=============================================================================
//
// タイトル画面処理 [title.cpp]
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
// マクロ定義
//*****************************************************************************
#define GAMEOVER_TEXTURENAME	L"data/texture/GameOver_02.png"	// テクスチャファイル名

#define GAMEOVER_POS_X		0								// ポリゴンの表示位置
#define GAMEOVER_POS_Y		0								// ポリゴンの表示位置
#define GAMEOVER_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMEOVER_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ
#define GAMEOVER_TIMER		(60+30)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static int g_nTimer;
//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT Initgameover()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMEOVER_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMEOVER_TIMER;

	return hr;
}

//=============================================================================
// 背景表示の終了処理
//=============================================================================
void Uninitgameover()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// 背景表示の更新処理
//=============================================================================
void Updategameover()
{
	// スペースキーを押したらゲーム開始
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
// 背景表示処理
//=============================================================================
void Drawgameover()
{
	// 背景描画
	SetPolygonPos(GAMEOVER_POS_X, GAMEOVER_POS_Y);
	SetPolygonSize(GAMEOVER_SIZE_X, GAMEOVER_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());
}
