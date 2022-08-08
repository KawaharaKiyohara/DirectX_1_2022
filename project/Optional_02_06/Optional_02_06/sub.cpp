#include "stdafx.h"

void InitLight(Light& light)
{
	//���C�g�͉E�����瓖�����Ă���B
	light.directionLight.direction.x = 1.0f;
	light.directionLight.direction.y = -1.0f;
	light.directionLight.direction.z = -1.0f;
	light.directionLight.direction.Normalize();
	//���C�g�̃J���[�͔��B
	light.directionLight.color.x = 0.5f;
	light.directionLight.color.y = 0.5f;
	light.directionLight.color.z = 0.5f;

	//���_�̈ʒu��ݒ肷��B
	light.eyePos = g_camera3D->GetPosition();
}
void InitModel(Model& model, Model& bgmodel, Light& light)
{
	//���f�������������邽�߂̏����\�z����B
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ肷��B
	modelInitData.m_fxFilePath = "Assets/shader/sample.fx";
	//�f�B���N�V�������C�g�̏���萔�o�b�t�@�Ƃ��ăf�B�X�N���v�^�q�[�v�ɓo�^���邽�߂�
	//���f���̏��������Ƃ��ēn���B
	modelInitData.m_expandConstantBuffer = &light;
	modelInitData.m_expandConstantBufferSize = sizeof(light);
	//�����������g���ă��f��������������B
	
	model.Init(modelInitData);
	model.UpdateWorldMatrix({ 0.0f, 50.0f, 0.0f }, g_quatIdentity, g_vec3One);
	modelInitData.m_tkmFilePath = "Assets/modelData/bg.tkm";
	bgmodel.Init(modelInitData);
}
void RotateLight(Light& light)
{
	Quaternion qRot;
	qRot.SetRotationDegY(g_pad[0]->GetLStickXF());
	qRot.Apply(light.directionLight.direction);
	qRot.SetRotationDegX(g_pad[0]->GetLStickYF());
	qRot.Apply(light.directionLight.direction);
}