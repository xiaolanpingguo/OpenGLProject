#include <windows.h>



/* 
	创建并显示窗口
*/


LRESULT CALLBACK GLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		// 发出一个WM_QUIT的消息给应用程序
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// 其他消息交给系统默认处理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	const LPCWSTR ClassName = L"GLWind";
	const LPCWSTR WndName = L"OpenGL Windows";

	// 窗口宽高和位置
	const int X = 100;
	const int Y = 200;
	const int Width = 800; 
	const int Height = 600;

	// 填充注册窗口的结构体
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;	// 窗口类型的额外储存空间
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;	
	wndclass.hbrBackground = NULL; // 窗口的背景
	wndclass.hCursor = NULL;	// 鼠标的光标
	wndclass.hIcon = NULL; // 生成的程序在文件夹中显示的图标
	wndclass.hIconSm = NULL; // 窗口的左上角的图标
	wndclass.hInstance = hInstance; // 本程序的实例
	wndclass.lpfnWndProc = GLWindowProc; // 消息回调函数
	wndclass.lpszClassName = ClassName; // 唯一的ID
	wndclass.lpszMenuName = NULL; // 菜单
	wndclass.style = CS_VREDRAW | CS_HREDRAW; // 水平和垂直重绘

	// 注册窗口
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		MessageBox(NULL, L"Register Fail", L"Error", MB_OK);
		return - 1;
	}

	// 创建窗口
	HWND hwnd = CreateWindowEx(NULL,	//额外的窗口风格
		ClassName, // 跟上面的className一样
		WndName,
		WS_OVERLAPPEDWINDOW,
		X, Y, Width, Height, NULL, NULL, hInstance, NULL);

	// 显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// 消息循环
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, 
			NULL, NULL, NULL, // 过滤的参数(NULL为不过滤)
			PM_REMOVE //取到消息后移除消息
		))
		{
			// 程序退出了
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// 转换消息并且派发给应用程序
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 开始绘制
	}

	return 0;
}

