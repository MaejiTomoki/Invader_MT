//=============================================================================
//
// �e���� [bullet.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
//#include "enemy.h"



//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ENEMYBULLET	1



//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct {
	int			nStat;	// ��� (0:����,1:�L��)
	XMFLOAT2	vPos;	// ���W
	XMFLOAT2	vVel;	// ���x
} ENEMYBULLET;



//=============================================================================
// �N���X
//=============================================================================
class CEnemyBullet
{
private:
	// �����o�ϐ�
	ID3D11ShaderResourceView*	m_pTexture;				// �e�N�X�`��

	static ENEMYBULLET						m_EnemyBullet[MAX_ENEMYBULLET];	// �e���
protected:

public:
	// �R���X�g���N�^/�f�X�g���N�^
	CEnemyBullet(void);
	~CEnemyBullet(void);

	// �l�又��
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �e�̔���
	int Fire(XMFLOAT2* pPos);

	// �e�̈ʒu�擾
	XMFLOAT2 GetEnemyBulletPos();

};


