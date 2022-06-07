//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "enemyUFO.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "collision.h"
#include "effect.h"
#include "score.h"
#include "EnemyBuller.h"
#include "fade.h"
#include "scene.h"
#include "enemy.h"




//*****************************************************************************
// グローバル変数
//*****************************************************************************
CBullet				g_BulletEnemyUFO;
XMFLOAT2			g_BulletEnemyUFOPos;
CEnemy				g_CEnemyUFO;
int					g_CEnemyUFOMoveCnt;
ENEMYUFO CEnemyUFO::m_enemyUFO[MAX_ENEMY_UFO_UFO];


// コンストラクタ/デストラクタ
CEnemyUFO::CEnemyUFO(void)
{

}
CEnemyUFO::~CEnemyUFO(void)
{

}



//=============================================================================
// 敵の初期化処理
//=============================================================================
HRESULT CEnemyUFO::Init()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &m_pTextureUFO[0]);
	if (FAILED(hr)) {
		return hr;
	}

	// 変数初期化
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		pEnemyUFO->nStat = 1;	// 有効
		pEnemyUFO->nDir = 2;
		pEnemyUFO->vVel = XMFLOAT2(0.5f, -20.0f);
		pEnemyUFO->vPos = XMFLOAT2(-1320.0f + i * 55, 1250.0f);
		CreateTextureFromFile(GetDevice(), ENEMY_TEXTURENAME_UFO, &m_pTextureUFO[i]);
	}

	return hr;
}



//=============================================================================
// 敵の終了処理
//=============================================================================
void  CEnemyUFO::Uninit()
{
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i)
	{
		// テクスチャ開放
		SAFE_RELEASE(m_pTextureUFO[i]);
	}
}



//=============================================================================
// 敵の更新処理
//=============================================================================
void  CEnemyUFO::Update()
{
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	
	// Ｙ軸の移動回数を持ってくる
	g_CEnemyUFOMoveCnt = g_CEnemyUFO.GetMoveCnt();

	// UFOの処理
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		if (pEnemyUFO->nStat == 0) {
			continue;	// 無効ならスキップ
		}

		// 2回移動するたびにUFO出現
		if ( g_CEnemyUFOMoveCnt == 1)		// 2回移動したの時
		{
			if (i == 0)
			{
				pEnemyUFO->vPos = XMFLOAT2(-420.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 3)		// 2回移動したの時
		{
			if (i == 1)
			{
				pEnemyUFO->vPos = XMFLOAT2(-520.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 4)		// 2回移動したの時
		{
			if (i == 2)
			{
				pEnemyUFO->vPos = XMFLOAT2(-920.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 7)		// 2回移動したの時
		{
			if (i == 3)
			{
				pEnemyUFO->vPos = XMFLOAT2(-420.0f, 250.0f);
			}
		}
		else if (g_CEnemyUFOMoveCnt == 9)		// 2回移動したの時
		{
			if (i == 4)
			{
				pEnemyUFO->vPos = XMFLOAT2(-820.0f, 250.0f);
			}
		}
		// 右方向の移動
		if (pEnemyUFO->nDir == 2)
		{
			pEnemyUFO->vPos.x += ENEMY_SPEED_X * 8;
		}
		// 左方向の移動
		else if (pEnemyUFO->nDir == 1)
		{
			pEnemyUFO->vPos.x -= ENEMY_SPEED_X + 1;
		}
	}
	// ===== 弾と敵の当たり判定 =====
		// 弾の位置を持ってくる
	g_BulletEnemyUFOPos = g_BulletEnemyUFO.GetBulletPos();
	// 当たり判定関数を使う
	CEnemyUFO::CollisionEnemyUFO(g_BulletEnemyUFOPos, 20);
	// ===== ここまで =====
}



//=============================================================================
// 敵の描画処理
//=============================================================================
void  CEnemyUFO::Draw()
{
	// 敵描画
	SetPolygonSize(ENEMY_UFO_SIZE_X, ENEMY_UFO_SIZE_Y);
	SetPolygonFrameSize(1.0f / ENEMY_UFO_FRAME_X, 1.0f / ENEMY_UFO_FRAME_Y);
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO) {
		if (pEnemyUFO->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		SetPolygonTexture(m_pTextureUFO[i]);
		SetPolygonPos(pEnemyUFO->vPos.x, pEnemyUFO->vPos.y);
		DrawPolygon(GetDeviceContext());
	}
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}




//=============================================================================
// 敵との衝突判定
//=============================================================================
int CEnemyUFO::CollisionEnemyUFO(XMFLOAT2 fB, float fBr)
{
	CScore Score;
	ENEMYUFO* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_UFO_UFO; ++i, ++pEnemyUFO)
	{
		if (pEnemyUFO->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		//	当たり判定
		if (CollisionCircle(pEnemyUFO->vPos, fB, ENEMY_SIZE_X / 2, fBr))
		{
			// 敵を消す
			pEnemyUFO->nStat = 0;
			// エフェクト
			StartEffect(&pEnemyUFO->vPos, EEFECT_DEAD000);
			// スコア
			Score.AddScore(100);

			return i;
		}

	}
	return -1;
}
