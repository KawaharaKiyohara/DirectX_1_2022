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

	//定数バッファを作成。
	ConstantBuffer cb, cb2;

	cb.Init(sizeof(Matrix));
	//テクスチャのブレンディング率を送るための定数バッファを初期化。
	cb2.Init(sizeof(float));
	
	//三角形ポリゴンを定義。
	TrianglePolygon triangle;
	triangle.Init(rootSignature);

	//step-1 三角形ポリゴンにUV座標を設定。
	triangle.SetUVCoord(
		0,			//頂点の番号
		0.0f,		//U座標
		1.0f		//V座標
	);

	triangle.SetUVCoord(
		1,			//頂点の番号
		0.5f,		//U座標
		0.0f		//V座標
	);

	triangle.SetUVCoord(
		2,			//頂点の番号
		1.0f,		//U座標
		1.0f		//V座標
	);

	//テクスチャをロード。
	Texture tex0, tex1;
	tex0.InitFromDDSFile(L"Assets/image/sample_00.dds");
	tex1.InitFromDDSFile(L"Assets/image/sample_01.dds");

	//ディスクリプタヒープを作成。
	DescriptorHeap ds;
	ds.RegistConstantBuffer(0, cb); //ディスクリプタヒープに定数バッファを登録。
	ds.RegistConstantBuffer(1, cb2);

	//テクスチャをディスクリプタヒープに登録。
	ds.RegistShaderResource(
		0,		//レジスタ番号
		tex0	//レジスタに設定するテクスチャ
	);
	ds.RegistShaderResource(
		1,		//レジスタ番号
		tex1	//レジスタに設定するテクスチャ
	);
	ds.Commit();					  //ディスクリプタヒープへの登録を確定。

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();
	//テクスチャをブレンディングするための変数。
	float addSpeed = 0.004f;
	float blendRate = 0.0f;
	float addRate = addSpeed;
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//フレーム開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//ルートシグネチャを設定。
		renderContext.SetRootSignature(rootSignature);
		//ブレンド率を変化させる。
		blendRate += addRate;
		if (blendRate > 1.0f) {
			addRate = -addSpeed;
			blendRate = 1.0f;
		}
		if (blendRate < 0.0f) {
			addRate = addSpeed;
			blendRate = 0.0f;
		}

		//ワールド行列を作成。
		Matrix mWorld;

		//ワールド行列をグラフィックメモリにコピー。
		cb.CopyToVRAM(mWorld);
		//ブレンド率を定数バッファにコピー。
		cb2.CopyToVRAM(blendRate);
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
