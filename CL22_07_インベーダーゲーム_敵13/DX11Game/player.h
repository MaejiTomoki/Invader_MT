//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 前地智貴
//
//=============================================================================
#pragma once

#include "main.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAME	L"data/texture/Player.png"	// テクスチャファイル名

#define	PLAYER_POS_X		0								// ポリゴンの表示位置
#define	PLAYER_POS_Y		-SCREEN_CENTER_Y + 100			// ポリゴンの表示位置
#define	PLAYER_SIZE_X		64								// ポリゴンのサイズ
#define	PLAYER_SIZE_Y		64								// ポリゴンのサイズ
#define PLAYER_FRAME_X		4								// 横フレーム数
#define PLAYER_FRAME_Y		4								// 縦フレーム数
#define PLAYER_SPEED_X		3			// 横移動速さ
#define PLAYER_SPEED_Y		2			// 縦移動速さ

#define PLAYER_RADIUS		28			// 当たり判定？

#define PLAYER_HP_SIZE_X	32								// HPの画像用
#define PLAYER_HP_SIZE_Y	32								// 
#define PLAYER_HP_POS_X		\
(-SCREEN_WIDTH/2+PLAYER_HP_SIZE_X)
#define PLAYER_HP_POS_Y		\
(SCREEN_HEIGHT/2-PLAYER_HP_SIZE_Y)




//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {
	int nPatNo;		// 表示パターン番号
	int nCount;		// 表示フレーム数
} ANIM_PAT;



class CPlayer
{
private:

protected:

public:
	// コンストラクタ/デストラクタ
	CPlayer(void);
	~CPlayer(void);

	// 四大処理
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// プレイヤーの位置取得
	XMFLOAT2 GetPlayerPos(void);

	// プレイヤーのサイズ取得
	XMFLOAT2 GetPlayerSixe(void);

	// プレイヤーの当たり判定
	int CollisionPlayer(XMFLOAT2 fB, float fBr);


	// メンバ変数
	ID3D11ShaderResourceView*	m_pTexture;			// テクスチャ

	int				m_nDir;							// 方向(0:下,1:左,2:右,3:上)
	XMFLOAT2		m_vPos;							// 座標
	int				m_nStat;						// 状態（0:無効1:有効）
	int				m_nHP;							// プレイヤーの体力
	int				m_nCntHP;						// 一定期間無敵
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

