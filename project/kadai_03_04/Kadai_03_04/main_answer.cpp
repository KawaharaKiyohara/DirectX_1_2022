#include "stdafx.h"
#include "system/system.h"
#include "TrianglePolygon.h"


//関数宣言
void InitRootSignature(RootSignature& rs);

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//ルートシグネチャを作成。
	RootSignature rootSignature;
	InitRootSignature(rootSignature);

	//三角形ポリゴンを定義。
	TrianglePolygon triangle;
	triangle.Init(rootSignature);

	//step-1 平行移動行列を送るための定数バッファを作成。
	ConstantBuffer cb;
	//行列は64バイトなので定数バッファのサイズに16を指定する。
	cb.Init(64);


	//ディスクリプタヒープを作成。
	DescriptorHeap ds;	
	//step-2 定数バッファをディスクリプタヒープに登録。
	ds.RegistConstantBuffer(0, cb);

	ds.Commit(); //ディスクリプタヒープへの登録を確定。

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-3 三角形の座標を表す変数を定義する。
	Vector3 trianglePos;
	trianglePos.x = 0.0f;
	trianglePos.y = 0.0f;
	trianglePos.z = 0.0f;

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//フレーム開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//step-4 コントローラーの入力で三角形を動かす。
		if (g_pad[0]->IsPress(enButtonRight))
		{
			trianglePos.x += 0.01f;
		}
		if (g_pad[0]->IsPress(enButtonLeft))
		{
			trianglePos.x -= 0.01f;
		}

		//step-5 三角形の座標を使って平行移動行列を作成する。
		Matrix mTrans;
		mTrans.MakeTranslation(trianglePos);

		//step-6 定数バッファに平行移動行列をコピーする。
		cb.CopyToVRAM(mTrans);

		//ルートシグネチャを設定。
		renderContext.SetRootSignature(rootSignature);		
		//ディスクリプタヒープを設定。
		renderContext.SetDescriptorHeap(ds);
		//三角形をドロー。
		triangle.Draw(renderContext);

		/// //////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//フレーム終了。
		g_engine->EndFrame();
	}
	return 0;
}


//ルートシグネチャの初期化。
void InitRootSignature(RootSignature& rs)
{
	rs.Init(D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}
