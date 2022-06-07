//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 前地智貴
//
//=============================================================================
#include "enemy.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "collision.h"
#include "effect.h"
#include "score.h"
#include "EnemyBuller.h"
#include "fade.h"
#include "scene.h"




//*****************************************************************************
// グローバル変数
//*****************************************************************************
CBullet				m_BulletEnemy;
XMFLOAT2			m_BulletEnemyPos;
ENEMY CEnemy::m_enemy[MAX_ENEMY_X];
//ENEMY CEnemy::m_enemyUFO[MAX_ENEMY_UFO];

int	g_nMoveCnt;				// Y(縦)の移動回数


// コンストラクタ/デストラクタ
CEnemy::CEnemy(void)
{

}
CEnemy::~CEnemy(void)
{

}



//=============================================================================
// 敵の初期化処理
//=============================================================================
HRESULT CEnemy::Init()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMY_TEXTURENAME, &m_pTexture[0]);
	if (FAILED(hr)) {
		return hr;
	}

	// 変数初期化
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) 
	{
		pEnemy->nStat = 1;	// 有効
		pEnemy->nDir = 2;
		pEnemy->vVel = XMFLOAT2(0.5f, -20.0f);
		if (i < 11)
		{
			// 3番上のタイプ
			pEnemy->nType = 3;

			pEnemy->vPos = XMFLOAT2(-320.0f + i * 55, 250.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME, &m_pTexture[i]);
		}
		else if (i>10 && i < 22)
		{
			// 2番上のタイプ
			pEnemy->nType = 2;

			pEnemy->vPos = XMFLOAT2(-925.0f + i * 55, 210.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME, &m_pTexture[i]);
		}
		else if (i > 21 && i < 33)
		{
			// ２番上のタイプ
			pEnemy->nType = 2;

			pEnemy->vPos = XMFLOAT2(-1530.0f + i * 55, 170.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME1, &m_pTexture[i]);
		}
		else if (i > 32 && i < 44)
		{
			// 一番上のタイプ
			pEnemy->nType = 1;

			pEnemy->vPos = XMFLOAT2(-2135.0f + i * 55, 130.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME1, &m_pTexture[i]);
		}
		else if (i > 43 && i < 55)
		{
			// 一番上のタイプ
			pEnemy->nType = 1;

			pEnemy->vPos = XMFLOAT2(-2740.0f + i * 55, 90.0f);
			CreateTextureFromFile(GetDevice(),
				ENEMY_TEXTURENAME2, &m_pTexture[i]);
		}
	}
	
	m_nTimer = rand() % FRAME_RATE + FRAME_RATE * 2;

	

	m_nDirection = 0;
	m_nCnt = 0;
	m_nEnemyCnt = 0;
	g_nMoveCnt = 0;

	return hr;
}



//=============================================================================
// 敵の終了処理
//=============================================================================
void  CEnemy::Uninit()
{
	for (int i = 0; i < MAX_ENEMY_X; ++i)
	{
		// テクスチャ開放
		SAFE_RELEASE(m_pTexture[i]);
	}
}



//=============================================================================
// 敵の更新処理
//=============================================================================
void  CEnemy::Update()
{
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy)
	{
		if (pEnemy->nStat == 0) {
 			m_nEnemyCnt++;
			continue;	// 無効ならスキップ
		}

		// 4回移動するたびに早くする
		if (g_nMoveCnt <= 4)	// 4以下の時
		{
			// 右方向の移動
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X;
			}
			// 左方向の移動
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X;
			}
		}
		else if (g_nMoveCnt <= 8)		// 8以下の時
		{
			// 右方向の移動
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X + 0.5f;
			}
			// 左方向の移動
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X + 0.5f;
			}
		}
		else	// 8以上の時
		{
			// 右方向の移動
			if (pEnemy->nDir == 2)
			{
				pEnemy->vPos.x += ENEMY_SPEED_X + 1;
			}
			// 左方向の移動
			else if (pEnemy->nDir == 1)
			{
				pEnemy->vPos.x -= ENEMY_SPEED_X + 1;
			}
		}

		//左制限
		if ((pEnemy->vPos.x < -SCREEN_WIDTH / 2 + ENEMY_SIZE_X / 2))
		{
			// 全てを書き換えるために初期に戻す
			pEnemy = m_enemy;
			// 一段下げて全て方向を変える
			for (int j = 0; j < MAX_ENEMY_X; ++j, ++pEnemy)
			{
				pEnemy->vPos.y -= 20;
				pEnemy->nDir = 2;
			}
			g_nMoveCnt++;
		}

		//右制限
		if ((pEnemy->vPos.x > SCREEN_WIDTH / 2 - ENEMY_SIZE_X / 2))
		{
			// 全てを書き換えるために初期に戻す
			pEnemy = m_enemy;
			for (int j = 0; j < MAX_ENEMY_X; ++j, ++pEnemy)
			{
				// 一段下げて全て方向を変える
				pEnemy->vPos.y -= 20;
				pEnemy->nDir = 1;
			}
			g_nMoveCnt++;
		}

		
		// ===== 弾と敵の当たり判定 =====
		// 弾の位置を持ってくる
		m_BulletEnemyPos = m_BulletEnemy.GetBulletPos();
		// 当たり判定関数を使う
		CEnemy::CollisionEnemy(m_BulletEnemyPos, 20);
		// ===== ここまで =====

		// -200以下になればゲームオーバー
		if (pEnemy->vPos.y < -200)
		{
			// ゲームオーバーシーンへ飛ぶ
			SetFadeOut(SCENE_GAMEOVER);
		}
	}

	// 敵が55体倒させたらクリア
	if (m_nEnemyCnt == MAX_ENEMY_X)
	{
		SetFadeOut(SCENE_GAMECLEAR);
	}
	else
	{
		m_nEnemyCnt = 0;
	}

	// ============ 敵の弾の処理 ============
	// ランダム関数を使って複数の敵(3)を選ぶ
	// --------------------------------------
	pEnemy = m_enemy;
	CEnemyBullet EnemyBullet;
	int nCnt;

	for (int i = 0; i < MAX_ENEMYBULLET; i++)
	{
		
		while (1)
		{
			nCnt = rand() % MAX_ENEMY_X;
			if (pEnemy[nCnt].nStat == 1)
			{
				break;
			}
		}
		
		for (int j = 0; j < nCnt; ++j, ++pEnemy)
		{
			if (nCnt - 1 == j)
			{
				EnemyBullet.Fire(&pEnemy->vPos);
			}
		}
	}


	m_nDirection++;
}



//=============================================================================
// 敵の描画処理
//=============================================================================
void  CEnemy::Draw()
{
	// 敵描画
	SetPolygonSize(ENEMY_SIZE_X, ENEMY_SIZE_Y);
	SetPolygonFrameSize(1.0f / ENEMY_FRAME_X, 1.0f / ENEMY_FRAME_Y);
	ENEMY* pEnemy = m_enemy;
	//ENEMY* pEnemyUFO = m_enemyUFO;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) {
		if (pEnemy->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		SetPolygonTexture(m_pTexture[i]);
		SetPolygonPos(pEnemy->vPos.x, pEnemy->vPos.y);
		DrawPolygon(GetDeviceContext());
	}
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// 敵との衝突判定
//=============================================================================
int CEnemy::CollisionEnemy( XMFLOAT2 fB, float fBr)
{
	CScore Score;
	ENEMY* pEnemy = m_enemy;
	for (int i = 0; i < MAX_ENEMY_X; ++i, ++pEnemy) 
	{
		if (pEnemy->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		//	当たり判定
 		if (CollisionCircle(pEnemy->vPos, fB, ENEMY_SIZE_X / 2, fBr))
		{
			// 敵を消す
 			pEnemy->nStat = 0;
			// エフェクト
			StartEffect(&pEnemy->vPos, EEFECT_DEAD000);

			if (pEnemy->nType == 1)
			{
				// スコア
				Score.AddScore(10);
			}
			if (pEnemy->nType == 2)
			{
				// スコア
				Score.AddScore(20);
			}
			if (pEnemy->nType == 3)
			{
				// スコア
				Score.AddScore(30);
			}
			

			return i;
		}
		
	}
	return -1;
}

//=============================================================================
// Y軸の移動回数を取得する
//=============================================================================
int CEnemy::GetMoveCnt()
{
	return g_nMoveCnt;
}


