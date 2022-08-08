#include "stdafx.h"
#include "system/system.h"
#include "TrianglePolygon.h"


//�֐��錾
void InitRootSignature(RootSignature& rs);

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

	//���[�g�V�O�l�`�����쐬�B
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//�O�p�`�|���S�����`�B
	TrianglePolygon triangle;
	triangle.Init(rootSignature);

	//step-1 ���s�ړ��s��𑗂邽�߂̒萔�o�b�t�@���쐬�B
	ConstantBuffer cb;
	//�s���64�o�C�g�Ȃ̂Œ萔�o�b�t�@�̃T�C�Y��16���w�肷��B
	cb.Init(64);


	//�f�B�X�N���v�^�q�[�v���쐬�B
	DescriptorHeap ds;	
	//step-2 �萔�o�b�t�@���f�B�X�N���v�^�q�[�v�ɓo�^�B
	ds.RegistConstantBuffer(0, cb);

	ds.Commit(); //�f�B�X�N���v�^�q�[�v�ւ̓o�^���m��B

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-3 �O�p�`�̍��W��\���ϐ����`����B
	Vector3 trianglePos;
	trianglePos.x = 0.0f;
	trianglePos.y = 0.0f;
	trianglePos.z = 0.0f;

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�t���[���J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//step-4 �R���g���[���[�̓��͂ŎO�p�`�𓮂����B
		if (g_pad[0]->IsPress(enButtonRight))
		{
			trianglePos.x += 0.01f;
		}
		if (g_pad[0]->IsPress(enButtonLeft))
		{
			trianglePos.x -= 0.01f;
		}

		//step-5 �O�p�`�̍��W���g���ĕ��s�ړ��s����쐬����B
		Matrix mTrans;
		mTrans.MakeTranslation(trianglePos);

		//step-6 �萔�o�b�t�@�ɕ��s�ړ��s����R�s�[����B
		cb.CopyToVRAM(mTrans);

		//���[�g�V�O�l�`����ݒ�B
		renderContext.SetRootSignature(rootSignature);		
		//�f�B�X�N���v�^�q�[�v��ݒ�B
		renderContext.SetDescriptorHeap(ds);
		//�O�p�`���h���[�B
		triangle.Draw(renderContext);

		/// //////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�t���[���I���B
		g_engine->EndFrame();
	}
	return 0;
}


//���[�g�V�O�l�`���̏������B
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}
