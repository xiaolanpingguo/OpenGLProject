#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")


/*
	����OpenGL��Ⱦ����
*/


LRESULT CALLBACK GLWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		// ����һ��WM_QUIT����Ϣ��Ӧ�ó���
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// ������Ϣ����ϵͳĬ�ϴ���
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	const LPCWSTR ClassName = L"GLWind";
	const LPCWSTR WndName = L"OpenGL Windows";

	// ���ڿ�ߺ�λ��
	const int X = 100;
	const int Y = 200;
	const int Width = 800;
	const int Height = 600;

	// ���ע�ᴰ�ڵĽṹ��
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;	// �������͵Ķ��ⴢ��ռ�
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL; // ���ڵı���
	wndclass.hCursor = NULL/*LoadCursor(NULL, IDC_IBEAM)*/;	// ���Ĺ��
	wndclass.hIcon = NULL; // ���ɵĳ������ļ�������ʾ��ͼ��
	wndclass.hIconSm = NULL; // ���ڵ����Ͻǵ�ͼ��
	wndclass.hInstance = hInstance; // �������ʵ��
	wndclass.lpfnWndProc = GLWindowProc; // ��Ϣ�ص�����
	wndclass.lpszClassName = ClassName; // Ψһ��ID
	wndclass.lpszMenuName = NULL; // �˵�
	wndclass.style = CS_VREDRAW | CS_HREDRAW; // ˮƽ�ʹ�ֱ�ػ�

	// ע�ᴰ��
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		MessageBox(NULL, L"Register Fail", L"Error", MB_OK);
		return -1;
	}

	// ��������
	HWND hwnd = CreateWindowEx(NULL,	//����Ĵ��ڷ��
		ClassName, // �������classNameһ��
		WndName,
		WS_OVERLAPPEDWINDOW,
		X, Y, Width, Height, NULL, NULL, hInstance, NULL);

	// ����OpenGL��Ⱦ������
	HDC dc = GetDC(hwnd);	//��ȡ���ڵ��豸
	PIXELFORMATDESCRIPTOR pfd;	// ��ɫ��ʽ������
	memset(&pfd, 0, sizeof(pfd));
	pfd.nVersion = 1;
	pfd.nSize = (sizeof(pfd));
	pfd.cColorBits = 32;	// ��ɫ������
	pfd.cDepthBits = 24;	// ��Ȼ�����
	pfd.cStencilBits = 8;	
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | // ��OpenGL��Ⱦ��������
		PFD_SUPPORT_OPENGL | // ��ɫ���ظ�ʽ֧��OpenGL
		PFD_DOUBLEBUFFER;	//֧��˫������

	// ����dcѡ����ɫ���ظ�ʽ������������
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormat, &pfd);

	// ����GL��Ⱦ�豸������
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	// set "clear color" for background, "clear color��һ������"
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);

	// ��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// ��Ϣѭ��
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg,
			NULL, NULL, NULL, // ���˵Ĳ���(NULLΪ������)
			PM_REMOVE //ȡ����Ϣ���Ƴ���Ϣ
		))
		{
			// �����˳���
			if (msg.message == WM_QUIT)
			{
				break;
			}

			// ת����Ϣ�����ɷ���Ӧ�ó���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// ��ʼ����

		// �øղ����õ���ɫȥ����
		glClear(GL_COLOR_BUFFER_BIT);

		// ����������
		SwapBuffers(dc);
	}

	return 0;
}

