#include "stdafx.h"
#include "system/system.h"

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
	
	//step-1 モデルをアニメーションさせるために必要なオブジェクトをすべて定義する。



	//step-2 スケルトンを初期化する。



	//step-3 モデルを初期化する。



	//step-4 アニメーションクリップをロードする。



	//step-10 アニメーションクリップにループ設定をする。



	//step-5 アニメーションの再生処理を初期化する。



	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//レンダリング開始。
		g_engine->BeginFrame();
		
		//step-9 アニメーションを切り替える。



		//step-6 アニメーションを進めるプログラムを追加。



		//step-7 アニメーション結果を元にスケルトンを更新。



		//step-8 モデルを描画。


		
		g_engine->EndFrame();
	}

	return 0;
}

