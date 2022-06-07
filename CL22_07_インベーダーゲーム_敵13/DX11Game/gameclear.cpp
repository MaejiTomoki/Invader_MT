//=============================================================================
//
// タイトル画面処理 [gameclear.cpp]
// Author : 前地智貴
//
//=============================================================================

// ===== 警告防止 =====
#define _CRT_SECURE_NO_WARNINGS

//#include "title.h"
#include<stdio.h>
#include<stdlib.h>
#include "gameclear.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "number.h"
#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMECLEAR_TEXTURENAME	L"data/texture/GameClear.png"	// テクスチャファイル名

#define GAMECLEAR_POS_X		0								// ポリゴンの表示位置
#define GAMECLEAR_POS_Y		0								// ポリゴンの表示位置
#define GAMECLEAR_SIZE_X		SCREEN_WIDTH					// ポリゴンのサイズ
#define GAMECLEAR_SIZE_Y		SCREEN_HEIGHT					// ポリゴンのサイズ
#define GAMECLEAR_TIMER		(60+20)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11ShaderResourceView*	g_pTexture;				// テクスチャ
static int							g_nTimer;
static int							g_nScoreGameClear;		// スコアの値
XMFLOAT2							g_vPosGameClear;		// 数字の位置
XMFLOAT2							g_vPosGameClearlastTime;// 前回スコアの数字の位置
CScore								g_ScoreGameClear;		// スコア
int									g_nScoreArra[5];		// スコア保存用
int									i;

//*****************************************************************************
// 構造体宣言部
//*****************************************************************************
typedef struct TScore
{
	//char szName[10 + 1];	//キャラ名
	int nScore;				//体力

	struct TScore *pNext;	//次のキャラへのポインタ

}Score;

//*****************************************************************************
// 関数プロトタイプ宣言
//*****************************************************************************
TScore *readFile(void);
void writeFile(TScore *pData);
void SetData(TScore * pSet);
void SetFillData();

//=============================================================================
// 背景表示の初期化処理
//=============================================================================
HRESULT InitgameClear()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		GAMECLEAR_TEXTURENAME, &g_pTexture);

	g_nTimer = GAMECLEAR_TIMER;

	g_vPosGameClear = XMFLOAT2(-210.0f, 130.0f);
	g_vPosGameClearlastTime = XMFLOAT2(-210.0f, -150.0f);

	TScore *pScore;

	// ファイルのデータを構造体配列へ読み込む
	pScore = readFile();

	// ファイルへリスト構造の内容を出力する
	writeFile(pScore);

	// ファイルの中身を配列に入れる
	SetData(pScore);

	return hr;
}

//=============================================================================
// 背景表示の終了処理
//=============================================================================
void UninitgameClear()
{
	//FILE *pFileOut;		// ファイルポインタ
	//
	//g_nScoreGameClear = g_ScoreGameClear.GetScore();
	//
	//Score ScoreList[1] =
	//{
	//	{ g_nScoreGameClear,NULL},
	//};
	//
	//// ファイルオープン
	//pFileOut = fopen("data/bin/Score.bin", "wb");
	//
	//// ファイルへ書き出し		
	//fwrite(ScoreList, sizeof(Score), 1, pFileOut);
	//
	//// ファイルクローズ
	//fclose(pFileOut);
	//
	// テクスチャ開放

	SetFillData();

	SAFE_RELEASE(g_pTexture);
}

//=============================================================================
// 背景表示の更新処理
//=============================================================================
void UpdategameClear()
{
	// スコアの値を持ってくる
	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	// デバッグ用
	// g_nScoreGameClear = g_nScoreArra[0];

	// スペースキーを押したらタイトル
	if (GetKeyRelease(VK_SPACE)) 
	{
		if (GetKeyRelease(VK_SPACE)) 
		{
			g_nScoreArra[0] = g_nScoreGameClear;
			SetFadeOut(SCENE_TITLE);
		}
	}
}

//=============================================================================
// 背景表示処理
//=============================================================================
void DrawgameClear()
{
	// 背景描画
	SetPolygonPos(GAMECLEAR_POS_X, GAMECLEAR_POS_Y);
	SetPolygonSize(GAMECLEAR_SIZE_X, GAMECLEAR_SIZE_Y);
	SetPolygonTexture(g_pTexture);
	DrawPolygon(GetDeviceContext());

	SetPolygonColor(0.0f, 1.0f, 0.0f);

	// スコア表示
	DrawNumber(&g_vPosGameClear,
		(unsigned)g_nScoreGameClear, SCORE_WIDTH,50,100);

	SetPolygonColor(1.0f, 0.0f, 0.0f);

	// 前回用
	DrawNumber(&g_vPosGameClearlastTime,
		(unsigned)g_nScoreArra[0], SCORE_WIDTH,50,100);
}

//=============================================================================
// ファイル読み込み関数
//=============================================================================
TScore *readFile(void)
{
	FILE *pFileIn;		// ファイルから読み込むようポインタ
	TScore *pData, *pRoot, *pBackUp;	//先頭とひとつ前のポインタ

	pRoot = NULL; //先頭データを初期化
	pBackUp = NULL;

	// ファイルオープン(読み込みモード、失敗したら終了)
	if ((pFileIn = fopen("data/bin/Score.bin", "rb")) == NULL)
		exit(EXIT_FAILURE);
	//データからデータ件数分、繰り返す
	while (1)
	{
		//動的メモリ確保(構造体party1データ分)
		pData = (TScore *)malloc(sizeof(TScore));

		// ファイルのデータを読みこんで今確保したメモリにのに格納
		//ただしデータが一件もなければメモリ開放
		//0件のファイルの時とファイルを全件読み込んだ後
		//							　 ↓データの個数
		if ((fread(pData, sizeof(TScore), 1, pFileIn)) < 1) {
			//		↑どこへ　↑1データのサイズ	　↑どこから

			free(pData);
			pData = NULL;
			break;
		}
		else //データを読み込めた場合
		{
			//一件目なら、先頭アドレスを保存
			if (pRoot == NULL)
			{
				pRoot = pData;
			}
			else//二件目以降なら、1つ前のデータとリストをつなぐ
			{
				pBackUp->pNext = pData;
			}

			//何件目でも共通処理
			//pNextをNULLにして最終データの目印を入れえる
			//現在のデータをバックアップする(次にの備える)
			pData->pNext = NULL;
			pBackUp = pData;

		}

	}

	// ファイルクローズ
	fclose(pFileIn);

	//先頭アドレスよりを戻り値として返す
	return pRoot;
}

//=============================================================================
// ファイル読み込み関数
//=============================================================================
void writeFile(TScore *pData)
{
	FILE *pFileOut;		// ファイルに書き出すタイプのポインタ
	// ファイルオープン(書き出しモード、ファイル無ければ)
	pFileOut = fopen("party.bin", "wb");

	// リスト構造の順番にファイルへ出力
	//pData = pRoot;
	while (pData)
	{
		fwrite(pData, sizeof(TScore), 1, pFileOut);
		pData = pData->pNext;	// 次のデータへ
	}

	// ファイルクローズ
	fclose(pFileOut);
}

//=============================================================================
// リスト構造表示関数
//=============================================================================
void SetData(TScore * pSet)
{
	////引数がNULLなら再帰を止めて戻る
	//if (pSet == NULL)// || g_nCntData == 5)
	//	return;
	//
	//// リストの順番で配列に保存
	//for (int i = 0; i < 5; i++)
	//{
	//	//引数がNULLなら再帰を止めて戻る
	//	if (pSet == NULL)
	//	{
	//		return;
	//	}
	//	g_nScoreArra[i] = pSet->nScore;
	//	pSet = pSet->pNext;
	//}
	//return;

	//引数がNULLなら再帰を止めて戻る
	if (pSet == NULL || i == 5)
		return;

	// リストの順番で配列に保存
	g_nScoreArra[i] = pSet->nScore;
	pSet = pSet->pNext;
	i++;

	//再帰呼び出しで次のデータを表示する
	SetData(pSet);
}

void SetFillData()
{
	FILE *pFileOut;		// ファイルポインタ

	g_nScoreGameClear = g_ScoreGameClear.GetScore();

	Score ScoreList[1] =
	{
		{ g_nScoreGameClear,NULL},
	};

	// ファイルオープン
	pFileOut = fopen("data/bin/Score.bin", "wb");

	// ファイルへ書き出し		
	fwrite(ScoreList, sizeof(Score), 1, pFileOut);

	// ファイルクローズ
	fclose(pFileOut);
}