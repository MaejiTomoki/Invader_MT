//=============================================================================
//
// 弾処理 [bullet.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "bullet.h"
#include "polygon.h"
#include "Texture.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_TEXTURENAME	L"data/texture/player000.png"	// テクスチャファイル名

#define BULLET_POS_X		0								// ポリゴンの表示位置
#define BULLET_POS_Y		0								// ポリゴンの表示位置
#define BULLET_SIZE_X		16								// ポリゴンのサイズ
#define BULLET_SIZE_Y		16								// ポリゴンのサイズ
#define BULLET_FRAME_X		4								// 横フレーム数
#define BULLET_FRAME_Y		4								// 縦フレーム数
#define BULLET_FRAME_NO		3								// フレームNo.
#define BULLET_SPEED_X		10								// 横移動速さ
#define BULLET_SPEED_Y		10								// 縦移動速さ

#define BULLET_RADIUS		30.0f
#define BULLET_STRENGTH		1.0f





//*****************************************************************************
// グローバル変数
//*****************************************************************************
BULLET CBullet::m_bullet[MAX_BULLET];
CEnemy m_EnemyBullet;


// コンストラクタ/デストラクタ
CBullet::CBullet(void)
{

}

CBullet::~CBullet(void)
{

}


//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT CBullet::Init()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		BULLET_TEXTURENAME, &m_pTexture);

	// 弾情報初期化
	for (int i = 0; i < MAX_BULLET; ++i) 
	{
		m_bullet[i].nStat = 0;
		m_bullet[i].vPos = XMFLOAT2(10000.0f, 1000.0f);
	}

	return hr;
}

//=============================================================================
// 弾の終了処理
//=============================================================================
void CBullet::Uninit()
{
	// テクスチャ開放
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CBullet::Update()
{
	// 弾の更新
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet) {
		if (pBullet->nStat == 0) {
			continue;	// 無効ならスキップ
		}
		// 移動
		pBullet->vPos.x += pBullet->vVel.x;
		pBullet->vPos.y += pBullet->vVel.y;
		// 画面の外に消えたか?
		if (pBullet->vPos.x <
			-(SCREEN_WIDTH + BULLET_SIZE_X) / 2.0f ||
			pBullet->vPos.x >=
			(SCREEN_WIDTH + BULLET_SIZE_X) / 2.0f ||
			pBullet->vPos.y <
			-(SCREEN_HEIGHT + BULLET_SIZE_Y) / 2.0f ||
			pBullet->vPos.y >=
			(SCREEN_HEIGHT + BULLET_SIZE_Y) / 2.0f) 
		{
			pBullet->nStat = 0;
			continue;
		}
		if (m_EnemyBullet.CollisionEnemy(pBullet->vPos, 20) >= 0)
		{
			// 表示しないようにする
			pBullet->nStat = 0;
			// 弾がその場に残ってしまうので初期化
			pBullet->vPos = XMFLOAT2(10000.0f, 10000.0f);

			continue;
		}
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
void CBullet::Draw()
{
	// 弾描画
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();
	SetPolygonSize(BULLET_SIZE_X, BULLET_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	SetPolygonFrameSize(1.0f / BULLET_FRAME_X, 1.0f / BULLET_FRAME_Y);
	int u = BULLET_FRAME_NO % BULLET_FRAME_X;
	int v = BULLET_FRAME_NO / BULLET_FRAME_X;
	SetPolygonUV(u / (float)BULLET_FRAME_X, v / (float)BULLET_FRAME_Y);
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet) {
		if (!pBullet->nStat) {
			// 無効なら次へ
			continue;
		}
		SetPolygonPos(pBullet->vPos.x, pBullet->vPos.y);
		DrawPolygon(pDeviceContext);
	}
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);
}



//=============================================================================
// 弾の発射処理
//=============================================================================
int CBullet::Fire(XMFLOAT2* pPos)
{
	BULLET* pBullet = m_bullet;
	for (int i = 0; i < MAX_BULLET; ++i, ++pBullet)
	{
		if (pBullet->nStat) {
			// 有効ならスキップ
			continue;
		}
		// 発射処理
		pBullet->vPos = *pPos;

		pBullet->vVel.x = 0.0f;
		pBullet->vVel.y = BULLET_SPEED_Y;

		pBullet->nStat = 1;
		return i;	// 発射成功
	}
	return -1;		// 発射不可
}



//=============================================================================
// 弾の発射処理
//=============================================================================
XMFLOAT2 CBullet::GetBulletPos()
{
	BULLET* pBullet = m_bullet;
	return pBullet->vPos;
}