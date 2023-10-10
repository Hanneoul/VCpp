#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);
	RECT rect = { 50, 50, 150, 150 }; // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (150, 150)������ �簢��
	HBRUSH hBrush;
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			isMouseLButtonPressed = 1;
			hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
			// �׸���
			FillRect(hdc, &rect, hBrush); // �簢���� ���������� ä���		
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_LEFT)
		{
			isMouseLButtonPressed = 0;

			hBrush = CreateSolidBrush(RGB(255, 255, 255)); // ��ũ �귯�� ����
			// �׸���
			FillRect(hdc, &rect, hBrush); // �簢���� ���������� ä���
		}
		break;

	case WM_PAINT:
	{	
		


	}
	break;
	case WM_CLOSE:
		PostQuitMessage(0);
		DestroyWindow(hwnd);

		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	ReleaseDC(hwnd, hdc);

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("�ļ� Application"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ���̱�.
	ShowWindow(hwnd, SW_SHOW); // â ����
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	// �޽��� ó��.
	while (msg.message != WM_QUIT)
	{	
		if (GetMessage(&msg, hwnd, 0, 0))
		{
			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);
		}
		//if(PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		//{
		//	// �޽��� �ؼ�����.
		//	TranslateMessage(&msg);
		//	// �޽����� ó���ؾ��� ���� ��������.
		//	DispatchMessage(&msg);
		//} // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		//else{}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//���� �޽��� ������
	return (int)msg.wParam;

}