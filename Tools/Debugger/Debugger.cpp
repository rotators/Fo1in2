#include "Debugger.h"
#include "Lib\diStorm\distorm.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

char codeDisplay[100000];
int codeLines = 0;

DWORD editorOffset;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEBUGGER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEBUGGER));

    MSG msg;

    codeDisplay[0] = '\0';
    //editorOffset = 0x410058;
    editorOffset = 0x41AB08; // audioRead_

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEBUGGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(30, 30, 30));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEBUGGER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HANDLE GetProcessByName(const wchar_t* processName)
{
    DWORD pid = 0;

    // Create toolhelp snapshot.
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes.
    if (Process32First(snapshot, &process))
    {
        do
        {
            // Compare process.szExeFile based on format of name, i.e., trim file path
            // trim .exe if necessary, etc.
            if (wcscmp(process.szExeFile, processName) == 0)
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);
    if (pid != 0)
    {
        return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    }

    return NULL;
}

void ReadBytes(HANDLE fo2, HWND window, int bytes)
{
    char hexbuf[3];
    char* buf = new char[(bytes * 2)];
    char* out = new char[(bytes*2)+1];
    
    ReadProcessMemory(fo2, (LPCVOID)editorOffset, buf, bytes, NULL);
   /* for (int i = 0; i < bytes; i++) {
        sprintf_s(hexbuf, "%x", buf[i] & 0xFF);
        out[(i * 2)] = hexbuf[0];
        out[(i * 2) + 1] = hexbuf[1];
    }
    out[(bytes * 2)] = '\0';*/

    _DecodeResult result;
    _DecodedInst disassembled[512];
    unsigned int instructionCount = 0;
    result = distorm_decode(0, (const unsigned char*)buf, bytes, Decode32Bits, disassembled, 100, &instructionCount);
    if (result != DECRES_SUCCESS)
    {
        MessageBoxA(NULL, "diStorm was unable to disassemble code.", "", MB_OK);
        return;
    }

    DWORD currentOffset = 0;
    codeDisplay[0] = '\0';
    codeLines = instructionCount;
    for (unsigned int i = 0; i < instructionCount; i++)
    {
        currentOffset = (DWORD)(editorOffset + disassembled[i].offset);
        sprintf_s(codeDisplay, "%s0x%x - %s %s\n", codeDisplay, currentOffset, (char*)disassembled[i].mnemonic.p, (char*)disassembled[i].operands.p);
    }

    InvalidateRect(window, 0, TRUE);


    //MessageBoxA(NULL, output, "", MB_OK);
}

void Attach(HWND window) {
    
    HANDLE fo2 = GetProcessByName(_T("Fallout2.exe"));
    ReadBytes(fo2, window, 200);
    
    
    //sprintf_s(out, "%x %x %x\n", buf[0] & 0xFF, buf[1] & 0xFF, buf[2] & 0xFF);
    
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_ATTACH:
                Attach(hWnd);
                //MessageBoxA(NULL, (LPCSTR)"Woop", (LPCSTR)"toop", MB_OK | MB_ICONEXCLAMATION);
                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT rect;
            HDC hdc = BeginPaint(hWnd, &ps);

            //windowBackgroundColor = RGB(0xff, 0xff, 0x00);
            //windowBackgroundBrush = CreateSolidBrush(windowBackgroundColor);
            //wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

            GetClientRect(hWnd, &rect);
            SetTextColor(hdc, RGB(0, 255, 60));
            SetBkMode(hdc, TRANSPARENT);

            HFONT hFont = CreateFont(11, 7, 0, 0, 0, FW_DONTCARE,
                false, false, ANSI_CHARSET,
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
                TEXT("Lucida Console")/*"SYSTEM_FIXED_FONT"*/);
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
            //DrawTextA(hdc, codeDisplay, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

            rect.left = 15;
            rect.top = 15;
            int i = 0;
            char* s = codeDisplay;
            int height = 0;
            //height = DrawTextA(hdc, "Fallout2.exe:", -1, &rect,
            //    DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
            //OffsetRect(&rect, 0, height);
            height = DrawTextA(hdc, s, -1, &rect,
                DT_WORDBREAK | DT_EDITCONTROL | DT_BOTTOM);
            OffsetRect(&rect, 0, height);
            s = *(environ + i);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
