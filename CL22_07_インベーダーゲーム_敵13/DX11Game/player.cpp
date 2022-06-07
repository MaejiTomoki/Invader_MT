//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "player.h"
#include "polygon.h"
#include "Texture.h"
#include "debugproc.h"
#include "input.h"
#include "bullet.h"
#include "flare.h"
#include "enemy.h"
#include "flare.h"
#include "scene.h"
#include "fade.h"
#include "effect.h"
#include "collision.h"
#include "EnemyBuller.h"





//*****************************************************************************
// グローバル変数
//*****************************************************************************
CBullet				BulletPlayer;			// クラスバレット



// コンストラクタ
CPlayer::CPlayer(void)
{

}


// デストラクタ
CPlayer::~CPlayer(void)
{
	 
}



//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CPlayer::Init()
{
	// テクスチャ読み込み
	HRESULT hr = CreateTextureFromFile(GetDevice(),
		PLAYER_TEXTURENAME, &m_pTexture);
	if (FAILED(hr)) {
		return hr;
	}

	// 変数初期化
	m_vPos.x = PLAYER_POS_X;
	m_vPos.y = PLAYER_POS_Y;
	m_nDir = 0;	// 下(待機)
	m_nStat = 1;
	m_nHP = 3;
	m_nCntHP = 0;

	return hr;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CPlayer::Uninit()
{
	// テクスチャ開放
	SAFE_RELEASE(m_pTexture);
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update()
{
	// プレイヤー移動
	m_nDir &= 3;	// 移動をクリア(方向は消さない)
	if (GetKeyPress(VK_A) || GetKeyPress(VK_LEFT)) {
		// 左移動
		m_vPos.x -= PLAYER_SPEED_X;
		m_nDir = 5;	// 左(移動)
	}
	if (GetKeyPress(VK_D) || GetKeyPress(VK_RIGHT)) {
		// 右移動
		m_vPos.x += PLAYER_SPEED_X;
		m_nDir = 6;	// 右(移動)
	}
	//if (GetKeyPress(VK_W) || GetKeyPress(VK_UP)) {
	//	// 上移動
	//	m_vPos.y += PLAYER_SPEED_Y;
	//	m_nDir = 7;	// 上(移動)
	//}
	//if (GetKeyPress(VK_S) || GetKeyPress(VK_DOWN)) {
	//	// 下移動
	//	m_vPos.y -= PLAYER_SPEED_Y;
	//	m_nDir = 4;	// 下(移動)
	//}

	//画面端
	// ===== 移動制限 =====
	//左制限
	if (m_vPos.x < -SCREEN_WIDTH / 2 + PLAYER_SIZE_X / 2)
	{

		m_vPos.x = -SCREEN_WIDTH / 2 + PLAYER_SIZE_X / 2;
	}

	//右制限
	if (m_vPos.x > SCREEN_WIDTH / 2 - PLAYER_SIZE_X / 2)
	{
		m_vPos.x = SCREEN_WIDTH / 2 - PLAYER_SIZE_X / 2;
	}
	// ===== ここまで =====

	// 弾の発射
	if (GetKeyTrigger(VK_SPACE)) {
		BulletPlayer.Fire(&m_vPos);
	}

	// フレア エフェクト起動 (加算合成テスト)
	if (GetKeyTrigger(VK_F)) {
		StartFlare(&m_vPos);
	}

	// 敵の弾と接触したか
	CEnemyBullet EnemyBulletPlayer;
	XMFLOAT2 EnemyBulletPos = EnemyBulletPlayer.GetEnemyBulletPos();

	if (CPlayer::CollisionPlayer(EnemyBulletPos, 10) >= 0)
	{
		// 一回しか当たらないようにする
		if (m_nCntHP == 0)
		{
			// プレイヤーの体力を減らす
			m_nHP--;
		}
		m_nCntHP++;
	}
	else
	{
		m_nCntHP = 0;
	}
	

	// HPが0になったらゲームオーバー
	if (m_nHP == 0)
	{
		// シーン移動(ゲームオーバー)
		SetFadeOut(SCENE_GAMEOVER);
	}
	//if (CollisionEnemy(m_vPos.x, m_vPos.y,
	//	PLAYER_RADIUS, 0.0f, &fX, &fY) >= 0) {
	//	// 爆発（？）
	//	m_nStat = 0;
	//	StartFlare(&m_vPos);
	//	m_nStat = 0;
	//	return;
	//}
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CPlayer::Draw()
{
	if (m_nStat == 0)return;

	// プレイヤー描画
	SetPolygonPos(m_vPos.x, m_vPos.y);
	SetPolygonSize(PLAYER_SIZE_X, PLAYER_SIZE_Y);
	SetPolygonTexture(m_pTexture);
	// SetPolygonFrameSize(1.0f / PLAYER_FRAME_X, 1.0f / PLAYER_FRAME_Y);
	DrawPolygon(GetDeviceContext());
	// フレームを戻しておく
	SetPolygonFrameSize(1.0f, 1.0f);
	SetPolygonUV(0.0f, 0.0f);

	// HP用
	for (int i = 0; i < m_nHP; i++)
	{
		SetPolygonPos(PLAYER_HP_POS_X + i * 32, PLAYER_HP_POS_Y);
		SetPolygonSize(PLAYER_HP_SIZE_X, PLAYER_HP_SIZE_Y);
		SetPolygonTexture(m_pTexture);
		DrawPolygon(GetDeviceContext());
	}
}



//=============================================================================
// プレイヤーとの衝突判定
//=============================================================================
int CPlayer::CollisionPlayer(XMFLOAT2 fB, float fBr)
{

	//	当たり判定
	if (CollisionCircle(m_vPos, fB, ENEMY_SIZE_X / 2, fBr))
	{
		// エフェクト
		StartEffect(&m_vPos, EEFECT_DEAD000);
		return 1;
	}


	return -1;
}