#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


/*
	画线
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
	wndclass.hCursor = NULL/*LoadCursor(NULL, IDC_IBEAM)*/;	// 鼠标的光标
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
		return -1;
	}

	// 创建窗口
	HWND hwnd = CreateWindowEx(NULL,	//额外的窗口风格
		ClassName, // 跟上面的className一样
		WndName,
		WS_OVERLAPPEDWINDOW,
		X, Y, Width, Height, NULL, NULL, hInstance, NULL);

	// 创建OpenGL渲染上下文
	HDC dc = GetDC(hwnd);	//获取窗口的设备
	PIXELFORMATDESCRIPTOR pfd;	// 颜色格式描述符
	memset(&pfd, 0, sizeof(pfd));
	pfd.nVersion = 1;
	pfd.nSize = (sizeof(pfd));
	pfd.cColorBits = 32;	// 颜色缓冲区
	pfd.cDepthBits = 24;	// 深度缓冲区
	pfd.cStencilBits = 8;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | // 把OpenGL渲染到窗口上
		PFD_SUPPORT_OPENGL | // 颜色像素格式支持OpenGL
		PFD_DOUBLEBUFFER;	//支持双缓冲区

	// 告诉dc选择颜色像素格式，并且设置它
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	// 创建GL渲染设备上下文
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	// 开始初始化
	glMatrixMode(GL_PROJECTION);	// 告诉显卡我要操作投影矩阵(选中了投影矩阵)
	gluPerspective(50.0f, // 角度
		800.0f / 600.0f,
		0.1f, 1000.0f);// 给投影矩阵设置参数
	glMatrixMode(GL_MODELVIEW);	// 告诉显卡我要操作模型视口矩阵
	glLoadIdentity();	// 单位矩阵，也就是先不对模型视口矩阵进行操作

	// set "clear color" for background, "clear color是一个整体"
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);

	// 显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW); // ccw: counter clock wind 逆时针方向

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
		glClear(GL_COLOR_BUFFER_BIT); // 用刚才设置的颜色去擦除

		// 画三角形
		//glBegin(GL_TRIANGLES);
		//glColor4ub(255, 0, 0, 255);
		//glVertex3f(0.0f, 0.0f, -10.0f);
		//glColor4ub(0, 255, 0, 255);
		//glVertex3f(-5.0f, 0.0f, -10.0f);
		//glColor4ub(0, 0, 255, 255);
		//glVertex3f(-5.0f, -2.0f, -10.0f);
		//glEnd();

		//glBegin(GL_TRIANGLE_STRIP);
		//glColor4ub(255, 0, 0, 255);
		//glVertex3f(0.0f, 0.0f, -10.0f);
		//glColor4ub(0, 255, 0, 255);
		//glVertex3f(-5.0f, 0.0f, -10.0f);
		//glColor4ub(0, 0, 255, 255);
		//glVertex3f(-5.0f, -2.0f, -10.0f);
		//glEnd();

		// 三角形扇
		//glBegin(GL_TRIANGLE_FAN);
		//glColor4ub(255, 0, 0, 255);
		//glVertex3f(0.0f, 0.0f, -10.0f);
		//glColor4ub(0, 255, 0, 255);
		//glVertex3f(-5.0f, 0.0f, -10.0f);
		//glColor4ub(0, 0, 255, 255);
		//glVertex3f(-5.0f, -2.0f, -10.0f);
		//glEnd();

		// 交换缓冲区
		SwapBuffers(dc);
	}

	return 0;
}

