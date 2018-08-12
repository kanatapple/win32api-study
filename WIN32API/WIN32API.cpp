#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM InitApp(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
HFONT MyCreateFont(int, DWORD, LPCSTR);

LPCWSTR szClassName = TEXT("WIN32API");

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow) {
	MSG msg;
	BOOL bRet;

	if (!InitApp(hCurInst))
		return FALSE;

	if (!InitInstance(hCurInst, nCmdShow))
		return FALSE;

	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (bRet == -1) {
			break;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

ATOM InitApp(HINSTANCE hInst) {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = (HICON)LoadImage(NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

	return RegisterClassEx(&wc);
}

BOOL InitInstance(HINSTANCE hInst, int nCmdShow) {
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Windowsプログラミング"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!hWnd)
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	/*
	{
		LPCTSTR lpszTxt = TEXT("Windowsプログラミング");
		HDC hdc;
		hdc = GetDC(hWnd);
		TextOut(hdc, 10, 10, lpszTxt, lstrlen(lpszTxt));
		ReleaseDC(hWnd, hdc);
	}
	*/
	return TRUE;
}

HFONT MyCreateFont(int nHeight, DWORD dwCharSet, LPCTSTR lpName) {
	return CreateFont(
		nHeight, 0, 0, 0,
		FW_DONTCARE,
		FALSE, FALSE, FALSE,
		dwCharSet,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		lpName
	);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HFONT hFont1, hFont2, hFont3;
	PAINTSTRUCT ps;
	HDC hdc;
	LPCTSTR lpszStr = TEXT("Windowsプログラミング");

	switch (msg) {
	case WM_CREATE:
		hFont1 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("HG行書体"));
		hFont2 = MyCreateFont(40, ANSI_CHARSET, TEXT("Fraktur JS"));
		hFont3 = MyCreateFont(40, SHIFTJIS_CHARSET, TEXT("ＭＳ明朝"));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hFont1);
		TextOut(hdc, 0, 0, lpszStr, lstrlen(lpszStr));
		SelectObject(hdc, hFont2);
		TextOut(hdc, 0, 60, lpszStr, lstrlen(lpszStr));
		SelectObject(hdc, hFont3);
		TextOut(hdc, 0, 120, lpszStr, lstrlen(lpszStr));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hFont1);
		DeleteObject(hFont2);
		DeleteObject(hFont3);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}
