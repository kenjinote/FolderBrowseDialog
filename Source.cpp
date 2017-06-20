#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include <shlobj.h>

TCHAR szClassName[] = TEXT("Window");

struct DATA
{
	LPCTSTR lpszName;
	DWORD dwID;
};

DATA data1[] = {
	{ TEXT("CSIDL_DESKTOP"),CSIDL_DESKTOP },
	{ TEXT("CSIDL_INTERNET"),CSIDL_INTERNET },
	{ TEXT("CSIDL_PROGRAMS"),CSIDL_PROGRAMS },
	{ TEXT("CSIDL_CONTROLS"),CSIDL_CONTROLS },
	{ TEXT("CSIDL_PRINTERS"),CSIDL_PRINTERS },
	{ TEXT("CSIDL_PERSONAL"),CSIDL_PERSONAL },
	{ TEXT("CSIDL_FAVORITES"),CSIDL_FAVORITES },
	{ TEXT("CSIDL_STARTUP"),CSIDL_STARTUP },
	{ TEXT("CSIDL_RECENT"),CSIDL_RECENT },
	{ TEXT("CSIDL_SENDTO"),CSIDL_SENDTO },
	{ TEXT("CSIDL_BITBUCKET"),CSIDL_BITBUCKET },
	{ TEXT("CSIDL_STARTMENU"),CSIDL_STARTMENU },
	{ TEXT("CSIDL_MYDOCUMENTS"),CSIDL_MYDOCUMENTS },
	{ TEXT("CSIDL_MYMUSIC"),CSIDL_MYMUSIC },
	{ TEXT("CSIDL_MYVIDEO"),CSIDL_MYVIDEO },
	{ TEXT("CSIDL_DESKTOPDIRECTORY"),CSIDL_DESKTOPDIRECTORY },
	{ TEXT("CSIDL_DRIVES"),CSIDL_DRIVES },
	{ TEXT("CSIDL_NETWORK"),CSIDL_NETWORK },
	{ TEXT("CSIDL_NETHOOD"),CSIDL_NETHOOD },
	{ TEXT("CSIDL_FONTS"),CSIDL_FONTS },
	{ TEXT("CSIDL_TEMPLATES"),CSIDL_TEMPLATES },
	{ TEXT("CSIDL_COMMON_STARTMENU"),CSIDL_COMMON_STARTMENU },
	{ TEXT("CSIDL_COMMON_PROGRAMS"),CSIDL_COMMON_PROGRAMS },
	{ TEXT("CSIDL_COMMON_STARTUP"),CSIDL_COMMON_STARTUP },
	{ TEXT("CSIDL_COMMON_DESKTOPDIRECTORY"),CSIDL_COMMON_DESKTOPDIRECTORY },
	{ TEXT("CSIDL_APPDATA"),CSIDL_APPDATA },
	{ TEXT("CSIDL_PRINTHOOD"),CSIDL_PRINTHOOD },
};

DATA data2[] = {
	{ TEXT("BIF_RETURNONLYFSDIRS"),BIF_RETURNONLYFSDIRS },
	{ TEXT("BIF_DONTGOBELOWDOMAIN"),BIF_DONTGOBELOWDOMAIN },
	{ TEXT("BIF_STATUSTEXT"),BIF_STATUSTEXT },
	{ TEXT("BIF_RETURNFSANCESTORS"),BIF_RETURNFSANCESTORS },
	{ TEXT("BIF_EDITBOX"),BIF_EDITBOX },
	{ TEXT("BIF_VALIDATE"),BIF_VALIDATE },
	{ TEXT("BIF_NEWDIALOGSTYLE"),BIF_NEWDIALOGSTYLE },
	{ TEXT("BIF_BROWSEINCLUDEURLS"),BIF_BROWSEINCLUDEURLS },
	{ TEXT("BIF_UAHINT"),BIF_UAHINT },
	{ TEXT("BIF_NONEWFOLDERBUTTON"),BIF_NONEWFOLDERBUTTON },
	{ TEXT("BIF_NOTRANSLATETARGETS"),BIF_NOTRANSLATETARGETS },
	{ TEXT("BIF_BROWSEFORCOMPUTER"),BIF_BROWSEFORCOMPUTER },
	{ TEXT("BIF_BROWSEFORPRINTER"),BIF_BROWSEFORPRINTER },
	{ TEXT("BIF_BROWSEINCLUDEFILES"),BIF_BROWSEINCLUDEFILES },
	{ TEXT("BIF_SHAREABLE"),BIF_SHAREABLE },
	{ TEXT("BIF_BROWSEFILEJUNCTIONS"),BIF_BROWSEFILEJUNCTIONS },
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton;
	static HWND hCheck[_countof(data2)];
	static HWND hCombo;
	static HWND hEdit1;
	static HWND hEdit2;
	switch (msg)
	{
	case WM_CREATE:
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		hCombo = CreateWindow(TEXT("COMBOBOX"), 0, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		{
			for (auto e : data1)
			{
				const DWORD_PTR nIndex = SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)e.lpszName);
				SendMessage(hCombo, CB_SETITEMDATA, nIndex, (LPARAM)e.dwID);
			}
			SendMessage(hCombo, CB_SETCURSEL, 0, 0);
			int i = 0;
			for (auto e : data2)
			{
				hCheck[i] = CreateWindow(TEXT("BUTTON"), e.lpszName, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
				if (e.dwID == BIF_RETURNONLYFSDIRS || e.dwID == BIF_NEWDIALOGSTYLE)
				{
					SendMessage(hCheck[i], BM_SETCHECK, BST_CHECKED, 0);
				}
				++i;
			}
		}
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("フォルダを選択してください。"), WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("フォルダー選択ダイアログを表示..."), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_READONLY | ES_AUTOHSCROLL, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_SIZE:
	{
		MoveWindow(hCombo, 10, 10, LOWORD(lParam) - 20, 32, TRUE);
		int i = 0;
		for (auto e : data2)
		{
			MoveWindow(hCheck[i], 10 + 256 * (i % 4), 50 + 40 * (i / 4), 256, 32, TRUE);
			++i;
		}
		MoveWindow(hEdit1, 10, 50 + 40 * ((i - 1) / 4) + 40, LOWORD(lParam) - 20, 64, TRUE);
		MoveWindow(hButton, 10, 50 + 40 * ((i - 1) / 4) + 40 + 64 + 10, LOWORD(lParam) - 20, 32, TRUE);
		MoveWindow(hEdit2, 10, 50 + 40 * ((i - 1) / 4) + 40 + 40 + 64 + 10, LOWORD(lParam) - 20, 32, TRUE);
	}
	break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			DWORD_PTR dwIndex = (DWORD_PTR)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			if (dwIndex == CB_ERR) return 0;
			DWORD_PTR dwID = SendMessage(hCombo, CB_GETITEMDATA, dwIndex, 0);
			LPITEMIDLIST pidlRoot = 0;
			if (SUCCEEDED(SHGetSpecialFolderLocation(hWnd, (int)dwID, &pidlRoot)))
			{
				BROWSEINFO  bi = { 0 };
				bi.hwndOwner = hWnd;
				bi.ulFlags = 0;
				int i = 0;
				for (auto e : data2)
				{
					if (SendMessage(hCheck[i], BM_GETCHECK, 0, 0))
					{
						bi.ulFlags += e.dwID;
					}
					++i;
				}
				const int nSize = GetWindowTextLength(hEdit1);
				LPTSTR lpszText = (LPTSTR)GlobalAlloc(0, sizeof(TCHAR) *(nSize + 1));
				GetWindowText(hEdit1, lpszText, nSize + 1);
				bi.lpszTitle = lpszText;
				bi.pidlRoot = pidlRoot;
				LPITEMIDLIST pidl = (LPITEMIDLIST)SHBrowseForFolder(&bi);
				LPMALLOC pMalloc = 0;
				if (pidl != NULL && SHGetMalloc(&pMalloc) != E_FAIL)
				{
					TCHAR szDirectoryPath[MAX_PATH];
					SHGetPathFromIDList(pidl, szDirectoryPath);
					SetWindowText(hEdit2, szDirectoryPath);
					SendMessage(hEdit2, EM_SETSEL, 0, -1);
					SetFocus(hEdit2);
					pMalloc->Free(pidl);
					pMalloc->Free(pidlRoot);
					pMalloc->Release();
				}
				GlobalFree(lpszText);
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