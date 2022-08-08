#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// �֐��錾
///////////////////////////////////////////////////////////////////
void InitLight(Light& light);
void InitModel(Model& model, Model& bgmodel, Light& light);
void RotateLight(Light& light);
void ExecuteTPSCamea(Vector3 teapotPos);

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	//�J�����̏������B
	g_camera3D->SetPosition({ 0.0f, 70.0f, 150.0f });
	g_camera3D->SetTarget({ 0.0f, 70.0f, 0.0f });

	//���C�g�̃f�[�^���쐬����B
	Light light;
	InitLight(light);

	//���f��������������B
	Model model, bgmodel;
	InitModel(model, bgmodel, light);

	Vector3 teapotPos;
	teapotPos.y = 20.0f;
	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();

		

		//�J�����̑O�x�N�g�������߂�B
		//	���_���璍���_�Ɍ������ĐL�т�x�N�g��V�����߂�B
		Vector3 cameraForward = g_camera3D->GetTarget() - g_camera3D->GetPosition();
		//Y�����͕s�v�B
		cameraForward.y = 0.0f;
		//�x�N�g��V�𐳋K�����āA�J�����̑O�����ɂ���B
		cameraForward.Normalize();

		//�J�����̉E�x�N�g�������߂�B
		Vector3 cameraRight;
		//�J�����̑O�����Ə�����̊O�ς����߂�B
		cameraRight.Cross( g_vec3Up, cameraForward);
		//���K������B
		cameraRight.Normalize();

		//�y�n���Y�I���z�A�i���O�X�e�B�b�N�𗘗p�����ړ���������������B
	
	
		

		//�e�B�[�|�b�g�̃��[���h�s����X�V����B
		//Model�N���X��UpdateWorldMatrix�֐����Ăяo���āA�e�B�[�|�b�g�̃��[���h�s����X�V����B
		model.UpdateWorldMatrix(
			teapotPos,			//�������͍��W�B
			g_quatIdentity,		//�������͉�]�N�H�[�^�j�I���Bg_quatIdentity�͒P�ʃN�H�[�^�j�I���B(��]�Ȃ�)
			g_vec3One			//��O�����͊g�嗦�Bg_vec3One��1,1,1�̃x�N�g���B���{�B
		);
		
		//TPS�J�����̐��������֐����Ăяo���B
		ExecuteTPSCamea(teapotPos);



		
		//�e�B�[�|�b�g���h���[�B
		model.Draw(renderContext);
		//�w�i���h���[�B
		bgmodel.Draw(renderContext);
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}
void ExecuteTPSCamea(Vector3 teapotPos)
{
	//�e�B�[�|�b�g�ɒǏ]�����鏈�������s�B
		//���݂̃J�����̎��_���擾����B
	Vector3 cameraPos = g_camera3D->GetPosition();
	//���݂̃J�����̃^�[�Q�b�g���擾����B
	Vector3 cameraTarget = g_camera3D->GetTarget();
	//���_���璍���_�Ɍ������ĐL�т�x�N�g�����v�Z����B
	Vector3 toCameraPos = cameraPos - cameraTarget;

	//�R���g���[���[�̓��͂�Y������ɉ�]����J�������쐬����B
	Quaternion qRotY;
	//g_pad[0]->GetRStickXF()�̓R���g���[���[�̉E�X�e�B�b�N�̓��͗ʂ��擾�ł���֐��B
	qRotY.SetRotationY(g_pad[0]->GetRStickXF() * 0.005f);
	//��]�N�H�[�^�j�I����toCameraPos���񂷁B
	qRotY.Apply(toCameraPos);

	Vector3 rotAxis;
	rotAxis.Cross(g_vec3AxisY, toCameraPos);
	rotAxis.Normalize();
	Quaternion qRotX;
	qRotX.SetRotation(rotAxis, g_pad[0]->GetRStickYF() * 0.005f);
	qRotX.Apply(toCameraPos);

	//�V���������_���e�B�[�|�b�g�̏�����ɐݒ肷��B
	cameraTarget = teapotPos;
	cameraTarget.y += 50.0f;
	//�V�������_���A�u�V���������_�@�{�@toCameraPos�v�ŋ��߂�B
	cameraPos = cameraTarget + toCameraPos;

	//�V�������_�ƒ����_���J�����ɐݒ肷��B
	g_camera3D->SetPosition(cameraPos);
	g_camera3D->SetTarget(cameraTarget);
}
