#include <Windows.h>
#include <cstdint>
#include <filesystem>//ファイルやディレクトリに関するライブラリ
#include <fstream>//ファイルに書き込み、読み込み
#include <chrono>//時間を扱う




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




void Log(std::ofstream& os, const std::string& message)
{
	os << message << std::endl;
	OutputDebugStringA(message.c_str());
}



//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

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
	


	//ファイル
	///
	//
	
	//ログのディレクトリを用意
	std::filesystem::create_directory("logs");

	
	//現在時刻を取得 (UTC時刻)
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	//ログファイルの名前にコンマ何秒を削って秒にする
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds>
	nowSeconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
	//日本時間(PCの設定時間)に変更
	std::chrono::zoned_time localTime{ std::chrono::current_zone(),nowSeconds };
	//formatを使って年月日_時分秒の文字列に変換
	std::string dateString = std::format("{:%Y%m%d_%H%M%S}", localTime);
	//時刻を使ってファイル名を決定
	std::string logFilePath = std::string("logs/") + dateString + ".log";
	//ファイルを作って書き込み準備
	std::ofstream logStream(logFilePath);





	

	




	//出力ウインドウへの文字出力
	OutputDebugStringA("Hello,DirectX!\n");


	













	return 0;
}