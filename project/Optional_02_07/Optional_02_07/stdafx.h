#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"


/// <summary>
/// �f�B���N�V�������C�g�\���́B
/// </summary>
struct DirectionLight {
	Vector3 direction;	//���C�g�̕����B	
	float pad0;
	Vector3 color;			//���C�g�̃J���[�B
	float pad1;
};
/// <summary>
/// ���C�g�\���́B
/// </summary>
struct Light {
	DirectionLight directionLight;		//�f�B���N�V�������C�g�B
	Vector3 eyePos;						//���_�̈ʒu�B
};

