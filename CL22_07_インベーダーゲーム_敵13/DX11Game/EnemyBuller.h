//=============================================================================
//
// 弾処理 [bullet.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
//#include "enemy.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ENEMYBULLET	1



//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct {
	int			nStat;	// 状態 (0:無効,1:有効)
	XMFLOAT2	vPos;	// 座標
	XMFLOAT2	vVel;	// 速度
} ENEMYBULLET;



//=============================================================================
// クラス
//=============================================================================
class CEnemyBullet
{
private:
	// メンバ変数
	ID3D11ShaderResourceView*	m_pTexture;				// テクスチャ

	static ENEMYBULLET						m_EnemyBullet[MAX_ENEMYBULLET];	// 弾情報
protected:

public:
	// コンストラクタ/デストラクタ
	CEnemyBullet(void);
	~CEnemyBullet(void);

	// 四大処理
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// 弾の発射
	int Fire(XMFLOAT2* pPos);

	// 弾の位置取得
	XMFLOAT2 GetEnemyBulletPos();

};


