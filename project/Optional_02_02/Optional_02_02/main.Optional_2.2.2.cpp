#include "stdafx.h"
#include "system/system.h"

///////////////////////////////////////////////////////////////////
// �֐��錾
///////////////////////////////////////////////////////////////////
void InitLight(Light& light);
void InitModel(Model& model, Model& bgmodel, Light& light);
void RotateLight(Light& light);

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
		
		//�e�B�[�|�b�g�𓮂����B
		teapotPos.x -= g_pad[0]->GetLStickXF();
		teapotPos.z -= g_pad[0]->GetLStickYF();

		//�y�n���Y�I���z�v���C���[��Ǐ]����J����
		//���݂̃J�����̎��_���擾����B
		Vector3 cameraPos = g_camera3D->GetPosition();
		//���݂̃J�����̃^�[�Q�b�g���擾����B
		Vector3 cameraTarget = g_camera3D->GetTarget();
		//���_���璍���_�Ɍ������ĐL�т�x�N�g�����v�Z����B
		Vector3 toCameraPos = cameraPos - cameraTarget;
		//�V���������_���e�B�[�|�b�g�̏�����ɐݒ肷��B
		cameraTarget = teapotPos;
		cameraTarget.y = 50.0f;
		//�V�������_���A�u�V���������_�@�{�@toCameraPos�v�ŋ��߂�B
		cameraPos = cameraTarget + toCameraPos;

		//�V�������_�ƒ����_���J�����ɐݒ肷��B
		g_camera3D->SetPosition(cameraPos);
		g_camera3D->SetTarget(cameraTarget);


		//�e�B�[�|�b�g�̃��[���h�s����X�V����B
		model.UpdateWorldMatrix(teapotPos, g_quatIdentity, g_vec3One);
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
