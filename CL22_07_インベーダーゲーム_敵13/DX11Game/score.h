//=============================================================================
//
// スコア表示処理 [score.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FRAME_TEXTURENAME	L"data/texture/frame_score.png"	// テクスチャファイル名

#define FRAME_SIZE_X		340								// ポリゴンのサイズ
#define FRAME_SIZE_Y		80								// ポリゴンのサイズ
#define FRAME_POS_X			\
(SCREEN_WIDTH/2-FRAME_SIZE_X/2)	// ポリゴンの表示位置
#define FRAME_POS_Y			\
(SCREEN_HEIGHT/2-FRAME_SIZE_Y/2)// ポリゴンの表示位置

#define SCORE_SIZE_X		35								// 文字のサイズ
#define SCORE_SIZE_Y		50								// 文字のサイズ
#define SCORE_WIDTH			8								// 表示桁数
#define SCORE_POS_X			\
(FRAME_POS_X-SCORE_SIZE_X*(SCORE_WIDTH/2))// 文字の表示位置
#define SCORE_POS_Y			\
(FRAME_POS_Y+SCORE_SIZE_Y/2-8)	// 文字の表示位置



//=============================================================================
// クラス
//=============================================================================
class CScore
{
private:
	// メンバ変数
	ID3D11ShaderResourceView*	m_pTexture;				// テクスチャ
	static int							m_nScore;
	XMFLOAT2						m_vPos;				// 数字の位置
protected:

public:
	// コンストラクタ/デストラクタ
	CScore(void);
	~CScore(void);

	// 四大処理
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// スコア取得
	int GetScore();

	// スコア加算
	void AddScore(int nValue);	
};




