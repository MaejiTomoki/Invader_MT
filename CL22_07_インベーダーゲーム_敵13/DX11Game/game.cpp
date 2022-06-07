//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "bullet.h"
#include "enemy.h"
#include "effect.h"
#include "flare.h"
#include "EnemyBuller.h"
#include "EnemyUFO.h"
/*#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
*/

//============================================================================
// グローバル変数
//============================================================================
CPlayer			Player;
CBullet			Bullet;
CEnemy			Enemy;
CScore			ScoreEnemy;
CEnemyBullet	EnemyBullet;
CEnemyUFO		EnemyUFO;

//=============================================================================
// ゲーム画面の初期化処理
//=============================================================================
HRESULT InitGame()
{
	// テクスチャ読み込み
	HRESULT hr = S_OK;

	// プレイヤー初期化
	hr = Player.Init();
	if (FAILED(hr)) {
		MsgBox(_T("プレイヤー初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 背景表示初期化
	hr = InitBG();
	if (FAILED(hr)) {
		MsgBox(_T("背景初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 弾処理初期化
	hr = Bullet.Init();
	if (FAILED(hr)) {
		MsgBox( _T("弾処理初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 敵処理初期化
	hr = Enemy.Init();
	if (FAILED(hr)) {
		MsgBox(_T("敵処理初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 敵(UFO)処理初期化
	hr = EnemyUFO.Init();
	if (FAILED(hr)) {
		MsgBox(_T("敵(UFO)処理初期化エラー"),
			MB_OK | MB_ICONSTOP);
		return hr;
	}

	// 敵の弾処理
	hr = EnemyBullet.Init();
	if (FAILED(hr)) {
		MsgBox(_T("敵の弾処理初期化エラー"),
			MB_OK | MB_ICONSTOP);
		return hr;
	}

	// エフェクト処理初期化
	hr = InitEffect();
	if (FAILED(hr)) {
		MsgBox(_T("エフェクト処理初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// フレア エフェクト処理初期化
	hr = InitFlare();
	if (FAILED(hr)) {
		MsgBox(_T("フレア エフェクト処理初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}

	// スコア表示処理初期化
	hr = ScoreEnemy.Init();
	if (FAILED(hr)) {
		MsgBox(_T("スコア表示処理初期化エラー"),
			 MB_OK | MB_ICONSTOP);
		return hr;
	}


	return hr;
}

//=============================================================================
// ゲーム画面の終了処理
//=============================================================================
void UninitGame()
{
	// スコア表示終了処理
	ScoreEnemy.Uninit();

	// フレア エフェクト終了処理
	UninitFlare();

	// エフェクト終了処理
	UninitEffect();

	// 敵の弾処理
	EnemyBullet.Uninit();

	// 敵(UFO)の処理
	EnemyUFO.Uninit();

	// 敵終了処理
	Enemy.Uninit();

	// 弾終了処理
	Bullet.Uninit();

	// 背景表示終了処理
	UninitBG();

	// プレイヤー終了処理
	Player.Uninit();

}

//=============================================================================
// ゲーム画面の更新処理
//=============================================================================
void UpdateGame()
{
	// 背景表示更新
	UpdateBG();

	// プレイヤー更新
	Player.Update();

	// 弾更新
	Bullet.Update();

	// 敵更新
	Enemy.Update();

	// 敵(UFO)更新
	EnemyUFO.Update();

	// 敵の弾処理
	EnemyBullet.Update();

	// エフェクト更新
	UpdateEffect();

	// フレア エフェクト更新
	UpdateFlare();

	// スコア更新
	ScoreEnemy.Update();
}

//=============================================================================
// ゲーム画面処理
//=============================================================================
void DrawGame()
{
	// 背景描画処理 (必ずClearRenderTargetViewの直後)
	DrawBG();

	// 敵描画処理
	Enemy.Draw();

	// 敵(FUO)描画処理
	EnemyUFO.Draw();

	EnemyBullet.Draw();

	// 弾描画処理
	Bullet.Draw();

	// プレイヤー描画処理
	Player.Draw();

	// エフェクト描画処理
	DrawEffect();

	// フレア エフェクト描画処理
	DrawFlare();

	// スコア描画処理
	ScoreEnemy.Draw();
}
