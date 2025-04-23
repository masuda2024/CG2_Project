#include <Windows.h>
#include <cstdint>
#include <filesystem>//ファイルやディレクトリに関するライブラリ
#include <fstream>//ファイルに書き込み、読み込み
#include <chrono>//時間を扱う

#include<string>
#include<format>


void Log(const std::string& message)
{
	OutputDebugStringA(message.c_str());
}



#pragma region 00_04-CPP

/**/
std::wstring ConvertString(const std::string& str)
{
	if (str.empty())
	{
		return std::wstring();
	}

	auto sizeNeeded = MultiByteToWideChar
	(
		CP_UTF8, 0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		NULL, 0
	);

	if (sizeNeeded == 0)
	{
		return std::wstring();
	}

	std::wstring result(sizeNeeded, 0);
	MultiByteToWideChar
	(
		CP_UTF8, 0,
		reinterpret_cast<const char*>(&str[0]),
		static_cast<int>(str.size()),
		&result[0], sizeNeeded
	);

}


std::string ConvertString(const std::wstring& str)
{
	if (str.empty())
	{
		return std::string();
	}

	auto sizeNeeded = WideCharToMultiByte
	(
		CP_UTF8, 0,
		str.data(),
		static_cast<int>(str.size()),
		NULL, 0, NULL, NULL
	);

	if (sizeNeeded == 0)
	{
		return std::string();
	}

	std::string result(sizeNeeded, 0);
	WideCharToMultiByte
	(
		CP_UTF8, 0, str.data(),
		static_cast<int>(str.size()),
		result.data(), sizeNeeded, NULL, NULL
	);


	return result;

}
#pragma endregion












//string->wstring
std::wstring ConvertString(const std::string& str);

//wstring->string
std::string ConvertString(const std::wstring& str);




















//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
		//ウインドウが破棄された
	case WM_DESTROY:
		//osに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}


	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);


}

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{




	//wstring->string
	Log(ConvertString(std::format(L"--------------------WSTRING{}\n",L"abc")));






	//ウインドウ
	///
	//


	
	//クライアント領域のサイズ
	const int32_t kClientWidth = 1280;
	const int32_t kClientHeight = 720;

	//ウインドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc = { 0,0,kClientWidth,kClientHeight };
	//クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);


	
   


	
	WNDCLASS wc{};
	//ウインドウプロシージャ
	wc.lpfnWndProc = WindowProc;
	//ウインドウクラス名
	wc.lpszClassName = L"CG2Window";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);


	//ウインドウクラスを登録する
	RegisterClass(&wc);
	


	//ウインドウの生成
	HWND hwnd = CreateWindow
	(
		wc.lpszClassName,     //利用するクラス名
		L"CG2",				  //タイトルバーの文字
		WS_OVERLAPPEDWINDOW,  //よく見るウインドウスタイル
		CW_USEDEFAULT,		  //表示X座標(Windousに任せる)
		CW_USEDEFAULT,		  //表示Y座標(Windousに任せる)
		wrc.right - wrc.left, //ウインドウ横幅
		wrc.bottom - wrc.top, //ウインドウ縦幅
		nullptr,			  //親ウインドウハンドル
		nullptr,			  //メニューハンドル
		wc.hInstance,		  //インスタンスハンドル
		nullptr				  //オプション
	);

	//ウインドウを表示する
	ShowWindow(hwnd, SW_SHOW);

	MSG msg{};
	//ウインドウのxボタンが押されるまでループ
	while (msg.message != WM_QUIT)
	{
		//windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else
		{
			//ゲームの処理

		}
	}
	


	//出力ウインドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");













	

	

	return 0;
}