#ifdef _DEBUG_
	#ifdef UNICODE
	#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

#include <windows.h>

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		{
			/** �簢�� �׸���
			*/
			//HDC hdc = GetDC(hwnd);
			//RECT rect = { 50, 50, 150, 150 }; // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (150, 150)������ �簢��
			//HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����

			//if (hBrush == NULL)
			//{
			//	MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
			//	exit(-1);	//����
			//}

			//// �׸���
			//FillRect(hdc, &rect, hBrush); // �簢���� ���������� ä���
			//ReleaseDC(hwnd, hdc);


			/** Ÿ�� �׸���
			*/
			//HDC hdc = GetDC(hwnd); // ����̽� ���ؽ�Ʈ ���
			//
			//HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
			//SelectObject(hdc, hBrush);

			//// Ÿ�� �׸���
			//Ellipse(hdc, 50, 50, 200, 150); // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (200, 150)������ Ÿ��

			//DeleteObject(hBrush);

			//ReleaseDC(hwnd, hdc); // ����̽� ���ؽ�Ʈ ����


		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return S_OK;	
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,	_In_ LPWSTR lpCmdLine,	_In_ int nShowCmd)
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

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);
			
		}
			/*else
			{

			}*/
	}

	//���� �޽��� ������
	return (int)msg.wParam;

}