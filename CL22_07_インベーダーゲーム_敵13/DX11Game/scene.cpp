//=============================================================================
//
// シーン遷移処理 [scene.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "gameclear02.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int 	g_nScene = SCENE_NOTE;				// 現在のシーン

//=============================================================================
// シーンの初期化処理
//=============================================================================
HRESULT InitScene()
{
	SetScene(SCENE_GAMECLEAR);// SCENE_TITLE);			// 最初はタイトル画面
	return S_OK;
}

//=============================================================================
// シーンの終了処理
//=============================================================================
void UninitScene()
{
	UninitgameClear();

	SetScene(SCENE_NOTE);			// 現在のシーンを終了
}

//=============================================================================
// シーンの更新処理
//=============================================================================
void UpdateScene()
{
	switch (g_nScene) 
	{
	case SCENE_TITLE:		// タイトル画面
		UpdateTitle();
		break;

	case SCENE_GAME:		// ゲーム画面
		UpdateGame();
		break;

	case SCENE_GAMEOVER:		// ゲーム画面
		Updategameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		UpdateGameClear02();
		break;

	case SCENR_RANKING:			// ランキング
		UpdategameClear();
		break;
	}
}

//=============================================================================
// シーン描画処理
//=============================================================================
void DrawScene()
{
	switch (g_nScene)
	{
	case SCENE_TITLE:		// タイトル画面
		DrawTitle();
		break;

	case SCENE_GAME:		// ゲーム画面
		DrawGame();
		break;

	case SCENE_GAMEOVER:		// ゲーム画面
		Drawgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		DrawGameClear02();
		break;

	case SCENR_RANKING:
		DrawgameClear();
		break;
	}
}

//=============================================================================
// シーン切り替え処理
//=============================================================================
void SetScene(int nScene)
{
	// 現在のシーンを終了
	switch (nScene)
	{
	case SCENE_TITLE:	// タイトル画面
		UninitTitle();
		break;

	case SCENE_GAME:	// ゲーム画面
		UninitGame();
		break;

	case SCENE_GAMEOVER:	// ゲーム画面
		Uninitgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		UninitGameClear02();
		break;

	case SCENR_RANKING:
		UninitgameClear();
		break;
	}
	g_nScene = nScene;
	// 次のシーンを初期化
	switch (nScene)
	{
	case SCENE_TITLE:	// タイトル画面
		InitTitle();
			break;

	case SCENE_GAME:	// ゲーム画面
		InitGame();
			break;

	case SCENE_GAMEOVER:	// ゲーム画面
		Initgameover();
		break;

	case SCENE_GAMECLEAR:		// ゲームクリア画面
		InitGameClear02();
		break;

	case SCENR_RANKING:
		InitgameClear();
		break;
	}
}
