#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"


/// <summary>
/// ディレクションライト構造体。
/// </summary>
struct DirectionLight {
	Vector3 direction;	//ライトの方向。	
	float pad0;
	Vector3 color;			//ライトのカラー。
	float pad1;
};
/// <summary>
/// ライト構造体。
/// </summary>
struct Light {
	DirectionLight directionLight;		//ディレクションライト。
	Vector3 eyePos;						//視点の位置。
};

