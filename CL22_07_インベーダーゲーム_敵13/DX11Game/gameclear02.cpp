//=============================================================================
//
// タイトル画面処理 [GameClear02.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "gameclear02.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMECLEAR02_TEXTURENAME	L"data/texture/GameClear_02.png"	// テクスチャファイル名

#define GAMECLEAR02_POS_X		0								// ポリゴンの表示位置
#define GAMECLEAR02_POS_Y		0								// ポリゴンの表示位置
#define GAMECLEAR02_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMECLEAR02_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ
#define GAMECLEAR02_TIMER		(60+30)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTextureGAMECLEAR02;				// テクスチャ
static int g_nTimerGAMECLEAR02;
//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitGameClear02()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR02_TEXTURENAME, &g_pTextureGAMECLEAR02);

	g_nTimerGAMECLEAR02 = GAMECLEAR02_TIMER;

	return hr;
}

//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitGameClear02()
{
	// テクスチャ開放
	SAFE_RELEASE(g_pTextureGAMECLEAR02);
}

//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdateGameClear02()
{
	// スペースキーを押したらゲーム開始
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
// 背景表示処理
//=============================================================================
void DrawGameClear02()
{
	// 背景描画
	SetPolygonPos(GAMECLEAR02_POS_X, GAMECLEAR02_POS_Y);
	SetPolygonSize(GAMECLEAR02_SIZE_X, GAMECLEAR02_SIZE_Y);
	SetPolygonTexture(g_pTextureGAMECLEAR02);
	DrawPolygon(GetDeviceContext());
}
