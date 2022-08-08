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

	//�萔�o�b�t�@���쐬�B
	ConstantBuffer cb, cb2;

	cb.Init(sizeof(Matrix));
	//�e�N�X�`���̃u�����f�B���O���𑗂邽�߂̒萔�o�b�t�@���������B
	cb2.Init(sizeof(float));
	
	//�O�p�`�|���S�����`�B
	TrianglePolygon triangle;
	triangle.Init(rootSignature);

	//step-1 �O�p�`�|���S����UV���W��ݒ�B
	triangle.SetUVCoord(
		0,			//���_�̔ԍ�
		0.0f,		//U���W
		1.0f		//V���W
	);

	triangle.SetUVCoord(
		1,			//���_�̔ԍ�
		0.5f,		//U���W
		0.0f		//V���W
	);

	triangle.SetUVCoord(
		2,			//���_�̔ԍ�
		1.0f,		//U���W
		1.0f		//V���W
	);

	//�e�N�X�`�������[�h�B
	Texture tex0, tex1;
	tex0.InitFromDDSFile(L"Assets/image/sample_00.dds");
	tex1.InitFromDDSFile(L"Assets/image/sample_01.dds");

	//�f�B�X�N���v�^�q�[�v���쐬�B
	DescriptorHeap ds;
	ds.RegistConstantBuffer(0, cb); //�f�B�X�N���v�^�q�[�v�ɒ萔�o�b�t�@��o�^�B
	ds.RegistConstantBuffer(1, cb2);

	//�e�N�X�`�����f�B�X�N���v�^�q�[�v�ɓo�^�B
	ds.RegistShaderResource(
		0,		//���W�X�^�ԍ�
		tex0	//���W�X�^�ɐݒ肷��e�N�X�`��
	);
	ds.RegistShaderResource(
		1,		//���W�X�^�ԍ�
		tex1	//���W�X�^�ɐݒ肷��e�N�X�`��
	);
	ds.Commit();					  //�f�B�X�N���v�^�q�[�v�ւ̓o�^���m��B

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	//�e�N�X�`�����u�����f�B���O���邽�߂̕ϐ��B
	float addSpeed = 0.004f;
	float blendRate = 0.0f;
	float addRate = addSpeed;
	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�t���[���J�n�B
		g_engine->BeginFrame();

		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////

		//���[�g�V�O�l�`����ݒ�B
		renderContext.SetRootSignature(rootSignature);
		//�u�����h����ω�������B
		blendRate += addRate;
		if (blendRate > 1.0f) {
			addRate = -addSpeed;
			blendRate = 1.0f;
		}
		if (blendRate < 0.0f) {
			addRate = addSpeed;
			blendRate = 0.0f;
		}

		//���[���h�s����쐬�B
		Matrix mWorld;

		//���[���h�s����O���t�B�b�N�������ɃR�s�[�B
		cb.CopyToVRAM(mWorld);
		//�u�����h����萔�o�b�t�@�ɃR�s�[�B
		cb2.CopyToVRAM(blendRate);
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
