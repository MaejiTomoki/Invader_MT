//=============================================================================
//
// 敵処理 [enemyUFO.h]
// Author : 前地智貴
//
//=============================================================================
#pragma once

#include "main.h"
#include "bullet.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_TEXTURENAME_UFO		L"data/texture/UFO.png"			// テクスチャファイル名


#define	ENEMY_UFO_POS_X			0								// ポリゴンの表示位置
#define	ENEMY_UFO_POS_Y			0								// ポリゴンの表示位置
#define	ENEMY_UFO_SIZE_X		50								// ポリゴンのサイズ
#define	ENEMY_UFO_SIZE_Y		50								// ポリゴンのサイズ
#define ENEMY_UFO_FRAME_X		1								// 横フレーム数
#define ENEMY_UFO_FRAME_Y		1								// 縦フレーム数
#define ENEMY_UFO_SPEED_X		0.5f							// 横移動速さ
#define ENEMY_UFO_SPEED_Y		0.5f							// 縦移動速さ

#define ENEMY_UFO_RADIUS		28

#define MAX_ENEMY_UFO_X			55
#define MAX_ENEMY_UFO_Y			5
				 
#define MAX_ENEMY_UFO_UFO		5



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
	int			nMoveCnt;	// Y(縦)の移動回数
	XMFLOAT2	vPos;		// 座標
	XMFLOAT2	vVel;		// 速度
} ENEMYUFO;


class CEnemyUFO
{
private:

protected:

public:
	// コンストラクタ/デストラクタ
	CEnemyUFO(void);
	~CEnemyUFO(void);

	//	四大処理
	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	int CollisionEnemyUFO(XMFLOAT2 fB, float fBr);

	// 変数
	ID3D11ShaderResourceView*	m_pTextureUFO[MAX_ENEMY_UFO_UFO];				// テクスチャUFO
	static ENEMYUFO m_enemyUFO[MAX_ENEMY_UFO_UFO];	// 敵情報(UFO)
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************



