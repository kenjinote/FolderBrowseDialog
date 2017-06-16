#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <shlobj.h>

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton;
	static HWND hEdit;
	switch (msg)
	{
	case WM_CREATE:
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("フォルダー選択ダイアログを表示..."), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
		MoveWindow(hButton, 10, 10, LOWORD(lParam) - 20, 32, TRUE);
		MoveWindow(hEdit, 10, 50, LOWORD(lParam) - 20, 32, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			LPITEMIDLIST pidlRoot = 0;
			if (SUCCEEDED(SHGetSpecialFolderLocation(hWnd, CSIDL_DRIVES, &pidlRoot)))
			{
				BROWSEINFO  bi = { 0 };
				bi.hwndOwner = hWnd;
				bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
				bi.lpszTitle = TEXT("フォルダを選択してください。");
				bi.pidlRoot = pidlRoot;
				LPITEMIDLIST pidl = (LPITEMIDLIST)SHBrowseForFolder(&bi);
				LPMALLOC pMalloc = 0;
				if (pidl != NULL && SHGetMalloc(&pMalloc) != E_FAIL)
				{
					TCHAR szDirectoryPath[MAX_PATH];
					SHGetPathFromIDList(pidl, szDirectoryPath);
					SetWindowText(hEdit, szDirectoryPath);
					SendMessage(hEdit, EM_SETSEL, 0, -1);
					SetFocus(hEdit);
					pMalloc->Free(pidl);
					pMalloc->Free(pidlRoot);
					pMalloc->Release();
				}
			}
		}
		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("フォルダー選択ダイアログ"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}