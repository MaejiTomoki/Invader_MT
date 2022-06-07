//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "EnemyBuller.h"
#include "polygon.h"
#include "Texture.h"
#include "player.h"
//#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMYBULLET_TEXTURENAME	L"data/texture/player000.png"	// テクスチャファイル名

#define ENEMYBULLET_POS_X		0								// ポリゴンの表示位置
#define ENEMYBULLET_POS_Y		0								// ポリゴンの表示位置
#define ENEMYBULLET_SIZE_X		16								// ポリゴンのサイズ
#define ENEMYBULLET_SIZE_Y		16								// ポリゴンのサイズ
#define ENEMYBULLET_FRAME_X		4								// 横フレーム数
#define ENEMYBULLET_FRAME_Y		4								// 縦フレーム数
#define ENEMYBULLET_FRAME_NO		3								// フレームNo.
#define ENEMYBULLET_SPEED_X		7								// 横移動速さ
#define ENEMYBULLET_SPEED_Y		7								// 縦移動速さ

#define ENEMYBULLET_RADIUS		30.0f
#define ENEMYBULLET_STRENGTH		1.0f





//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMYBULLET CEnemyBullet::m_EnemyBullet[MAX_ENEMYBULLET];
CPlayer m_PlayerColl;


// コンストラクタ/デストラクタ
CEnemyBullet::CEnemyBullet(void)
{

}

CEnemyBullet::~CEnemyBullet(void)
{

}


//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CEnemyBullet::Init()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		ENEMYBULLET_TEXTURENAME, &m_pTexture);

	// 弾情報初期化
	for (int i = 0; i < MAX_ENEMYBULLET; ++i)
	{
		m_EnemyBullet[i].nStat = 0;
		m_EnemyBullet[i].vPos = XMFLOAT2(10000.0f, 10000.0f);
	}

	return hr;
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void CEnemyBullet::Uninit()
{
	// テクスチャ開放
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyBullet::Update()
{
	// 弾の更新
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet) {
		if (pEnemyBullet->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		// 移動
		pEnemyBullet->vPos.x += pEnemyBullet->vVel.x;
		pEnemyBullet->vPos.y += pEnemyBullet->vVel.y;
		// 画面の外に消えたか?
		if (pEnemyBullet->vPos.x <
			-(SCREEN_WIDTH + ENEMYBULLET_SIZE_X) / 2.0f ||
			pEnemyBullet->vPos.x >=
			(SCREEN_WIDTH + ENEMYBULLET_SIZE_X) / 2.0f ||
			pEnemyBullet->vPos.y <
			-(SCREEN_HEIGHT + ENEMYBULLET_SIZE_Y) / 2.0f ||
			pEnemyBullet->vPos.y >=
			(SCREEN_HEIGHT + ENEMYBULLET_SIZE_Y) / 2.0f) 
		{
			pEnemyBullet->nStat = 0;
			continue;
		}

		//if (m_PlayerColl.CollisionPlayer(pEnemyBullet->vPos, 10) >= 0)
		//{
		//	// 表示しないようにする
		//	pEnemyBullet->nStat = 0;
		//	// 弾がその場に残ってしまうので初期化
		//	pEnemyBullet->vPos = XMFLOAT2(10000.0f, 10000.0f);

		//	continue;
		//}
		// 敵との当たり判定
		//if (CollisionEnemy(pBullet->vPos.x,pBullet->vPos.y, 
		//	BULLET_RADIUS,BULLET_STRENGTH, nullptr, nullptr) >= 0) 
		//{
		//	pBullet->nStat = 0;
		//	continue;
		//}
	}
}

//=============================================================================
// 弾の描画処理
//=============================================================================
void CEnemyBullet::Draw()
{
	// 弾描画
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonSize(ENEMYBULLET_SIZE_X, ENEMYBULLET_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / ENEMYBULLET_FRAME_X, 1.0f / ENEMYBULLET_FRAME_Y);
	int u = ENEMYBULLET_FRAME_NO % ENEMYBULLET_FRAME_X;
	int v = ENEMYBULLET_FRAME_NO / ENEMYBULLET_FRAME_X;
	SetPolygonUV(u / (float)ENEMYBULLET_FRAME_X, v / (float)ENEMYBULLET_FRAME_Y);

	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet) {
		if (!pEnemyBullet->nStat) {
			// 無効なら次へ
			continue;
		}
		SetPolygonPos(pEnemyBullet->vPos.x, pEnemyBullet->vPos.y);
		DrawPolygon(pDeviceContext);
	}
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// 弾の発射処理
//=============================================================================
int CEnemyBullet::Fire(XMFLOAT2* pPos)
{
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	for (int i = 0; i < MAX_ENEMYBULLET; ++i, ++pEnemyBullet)
	{
		if (pEnemyBullet->nStat) {
			// 有効ならスキップ
			continue;
		}
		// 発射処理
		pEnemyBullet->vPos = *pPos;

		pEnemyBullet->vVel.x = 0.0f;
		pEnemyBullet->vVel.y = -ENEMYBULLET_SPEED_Y;

		pEnemyBullet->nStat = 1;
		return i;	// 発射成功
	}
	return -1;		// 発射不可
}



//=============================================================================
// 弾の位置取得
//=============================================================================
XMFLOAT2 CEnemyBullet::GetEnemyBulletPos()
{
	ENEMYBULLET* pEnemyBullet = m_EnemyBullet;
	return pEnemyBullet->vPos;
}


