#include "stdafx.h"
#include "system/system.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//step-1 3Dモデルをロードする。
	//ロードするための初期化情報を作成。
	ModelInitData initData;
	//tkmファイルのファイルパス。
	initData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	//使用するシェーダーのファイルパス。
	initData.m_fxFilePath = "Assets/shader/Sample.fx";
	//作成した初期化情報を使って、初期化する。
	Model charaModel;
	charaModel.Init(initData);

	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	//step-3 キャラの位置、回転、拡大率を表す変数を定義する。
	Vector3 pos;
	Quaternion rot;
	Vector3 scale;
	//拡大率はx、y、zを1で初期化しておく。
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();

		//////////////////////////////////////
		//ここから絵を描くコードを記述する。
		//////////////////////////////////////

		//step-4 コントローラーの入力でキャラを動かす。
		pos.x += g_pad[0]->GetLStickXF();

		//step-5 コントローラーの入力でキャラをY軸周りに回転させる。
		Quaternion addRot;
		addRot.SetRotationY(g_pad[0]->GetRStickXF() * 0.01f );
		//クォータニオンは掛け算で回転を合成できる。
		rot *= addRot ;

		//step-6 コントローラーの入力でキャラをX軸方向に拡大させる。
		if (g_pad[0]->IsPress(enButtonLeft)) {
			scale.x += 0.01f;
		}
		if (g_pad[0]->IsPress(enButtonRight)) {
			scale.x -= 0.01f;
		}

		//step-7 平行移動、回転、拡大率を利用してワールド行列を計算する。
		charaModel.UpdateWorldMatrix(pos, rot, scale);

		//step-2 3Dモデルをドローする。
		charaModel.Draw(renderContext);


		//////////////////////////////////////
		//絵を描くコードを書くのはここまで！！！
		//////////////////////////////////////
		//レンダリング終了。
		g_engine->EndFrame();
	}
	return 0;
}