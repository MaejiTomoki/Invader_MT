//=============================================================================
//
// 敵処理 [enemy.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "bullet.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_TEXTURENAME			L"data/texture/enemy1.png"		// テクスチャファイル名
#define ENEMY_TEXTURENAME1			L"data/texture/enemy2.png"		// テクスチャファイル名
#define ENEMY_TEXTURENAME2			L"data/texture/enemy3.png"		// テクスチャファイル名
#define ENEMY_TEXTURENAME_1			L"data/texture/enemy1_2.png"	// テクスチャファイル名
#define ENEMY_TEXTURENAME1_1		L"data/texture/enemy2._2png"	// テクスチャファイル名
#define ENEMY_TEXTURENAME2_1		L"data/texture/enemy3_2.png"	// テクスチャファイル名


#define	ENEMY_POS_X			0								// ポリゴンの表示位置
#define	ENEMY_POS_Y			0								// ポリゴンの表示位置
#define	ENEMY_SIZE_X		50								// ポリゴンのサイズ
#define	ENEMY_SIZE_Y		50								// ポリゴンのサイズ
#define ENEMY_FRAME_X		1								// 横フレーム数
#define ENEMY_FRAME_Y		1								// 縦フレーム数
#define ENEMY_SPEED_X		0.5f							// 横移動速さ
#define ENEMY_SPEED_Y		0.5f							// 縦移動速さ

#define ENEMY_RADIUS		28

#define MAX_ENEMY_X			55
#define MAX_ENEMY_Y			5

//#define MAX_ENEMY_UFO		5



//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {
	int			nType;		// 種類(0:スライム)
	int			nStat;		// 状態(0:無効,1:有効)
	int			nDir;		// 方向(0:下,1:左,2:右,3:上)
	int			nTimer;		// 方向変更用
	int			nAnim;		// 再生位置
	int			nCount;		// 再生フレーム数
	int			nDirStat;
	XMFLOAT2	vPos;		// 座標
	XMFLOAT2	vVel;		// 速度
} ENEMY;


class CEnemy
{
private:
	
protected:

public:
	// コンストラクタ/デストラクタ
	CEnemy(void);
	~CEnemy(void);

	//	四大処理
	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	int CollisionEnemy(XMFLOAT2 fB, float fBr);
	int GetMoveCnt();			// Y軸の移動回数

	// 変数
	ID3D11ShaderResourceView*	m_pTexture[MAX_ENEMY_X];				// テクスチャ
	//ID3D11ShaderResourceView*	m_pTextureUFO[MAX_ENEMY_UFO];				// テクスチャUFO
	static ENEMY m_enemy[MAX_ENEMY_X];	// 敵情報
	//static ENEMY m_enemyUFO[MAX_ENEMY_UFO];	// 敵情報(UFO)
	int m_nTimer;				// 敵生成タイマー
	int m_nDirection;			// 敵の向かう移動回数
	int m_nCnt;					// 敵の動きのカウント
	int m_nEnemyCnt;			// 敵のカウント数
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************



